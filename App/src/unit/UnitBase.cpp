// UnitBase class

# include "UnitBase.hpp"

using namespace Config::Player;

UnitBase::UnitBase()
	: m_hasMoved{ false }
	, m_completedAction{ false }
	, m_startPosition{ m_playerPosition }
	, m_prevPosition{ m_playerPosition }
{

}

void UnitBase::update(const double deltaTime, const Vec3& cameraForward)
{
	if (!m_hasMoved)
	{
		move(deltaTime, cameraForward);

		if (PlayerInput::KeyConfirm())
		{
			m_hasMoved = true;
		}
	}

	if (PlayerInput::KeyCancel())
	{
		m_hasMoved = false;
	}
	
}

void UnitBase::drawUI() const
{
	// 移動範囲の描画
	Util::DrawDiscFrame(m_startPosition, m_moveRangeRadius, 10);

	// 攻撃範囲の描画
	const Disc attackRangeDisc{ Vec3{ m_playerPosition.x, 0.0001, m_playerPosition.z }, m_attackRangeRadius };
	attackRangeDisc.draw(ColorF{ 0, 1, 0.498, 0.7 }.removeSRGBCurve());
}

void UnitBase::move(const double deltaTime, const Vec3& cameraForward)
{
	// 平面移動ベクトル(x : 左右, y : 前後)
	const Vec2 movementVector2D{ PlayerInput::GetMovementAxis() };

	// 移動入力がなければそのままreturn
	if (movementVector2D.isZero())
	{
		return;
	}

	// カメラの向きを基準にした右向きベクトル
	const Vec3 rightVector{ -cameraForward.cross(Vec3::Up()).normalized() };

	// 空間移動ベクトル
	Vec3 velocity{ movementVector2D.y * cameraForward + movementVector2D.x * rightVector };

	if (!velocity.isZero())
	{
		// Y軸回転角度を計算
		const double angleY{ Atan2(velocity.x, velocity.z) };
		m_playerRotation = m_playerRotation.slerp(Quaternion::RotateY(angleY), RotateSpeed * deltaTime);
	}

	// 停止ボタンの判定
	if (PlayerInput::StopMove())
	{
		return;
	}

	// ダッシュ中かの判定
	const float moveSpeed{ PlayerInput::KeyDash() ? MoveSpeed::Sprint : MoveSpeed::Default };

	// モデル描画位置を移動
	m_playerPosition.moveBy(velocity * moveSpeed * deltaTime);

	// 移動範囲の制限
	if (m_playerPosition.distanceFrom(m_startPosition) <= m_moveRangeRadius)
	{
		// 移動範囲内であれば、直前座標を更新
		m_prevPosition = m_playerPosition;
	}
	else
	{
		// 範囲外であれば、直前座標にとどまる
		m_playerPosition = m_prevPosition;
	}
}

uint8 UnitBase::getMaxHp() const
{
	return m_maxHp;
}

uint8 UnitBase::getCurrentHp() const
{
	return m_currentHp;
}

String UnitBase::getUnitName() const
{
	return m_unitName;
}
