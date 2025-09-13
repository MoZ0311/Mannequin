// PlayerCharacter class

# include "PlayerCharacter.hpp"
#include "../core/ModelAssets.hpp"

using namespace Config::Player;

PlayerCharacter::PlayerCharacter()
	: m_playerPosition{ 0.0, 0.0, 0.0 }
	, m_playerRotation{ 0, 0, 0, 0 }
	, m_animationArray{ ModelAssets::GetInstance().idleAnimationArray }
	, m_attackInputBuffer{}
	, m_animationTimer{ 0.0 }
	, m_isAttacking{ false }
{

}

void PlayerCharacter::update(const double deltaTime, const Vec3& cameraForward)
{
	// コマンドに対応したアニメーションを蓄積
	if (PlayerInput::KeyLiteAttack() && m_attackInputBuffer.size() < MaxBufferSize)
	{
		m_attackInputBuffer.push(ModelAssets::GetInstance().attackAnimationArray);
	}

	move(deltaTime, cameraForward);
	animationUpdate();
}

void PlayerCharacter::draw() const
{
	// double型のタイマーを切り捨てて整数値に
	uint8 index{ static_cast<uint8>(Floor(m_animationTimer)) };

	// 対応するアニメーション配列のモデルを描画
	m_animationArray[index].draw(m_playerPosition, m_playerRotation);
}

void PlayerCharacter::move(const double deltaTime, const Vec3& cameraForward)
{
	// 平面移動ベクトル(x : 左右, y : 前後)
	const Vec2& movementVector2D{ PlayerInput::GetMovementAxis() };

	// 移動入力がなければそのままreturn
	if (movementVector2D.isZero() || PlayerInput::KeyGuard())
	{
		return;
	}

	// カメラの向きを基準にした右向きベクトル
	const Vec3& rightVector{ -cameraForward.cross(Vec3::Up()).normalized() };

	// 空間移動ベクトル
	const Vec3& velocity{ movementVector2D.y * cameraForward + movementVector2D.x * rightVector };

	// 念の為0ベクトルでないかのチェックう
	if (!velocity.isZero())
	{
		// Y軸回転角度を計算
		const double angleY{ Atan2(velocity.x, velocity.z) };

		if (m_isAttacking)
		{
			if (m_animationTimer < Scene::DeltaTime())
			{
				// 攻撃の出始めに自由な方向へ即時方向転換可能
				m_playerRotation = Quaternion::RotateY(angleY);
			}
			// 出始め以降は回転も移動も不可
			return;
		}

		// 線形補正をかけながらプレイヤーを回転
		m_playerRotation = m_playerRotation.slerp(Quaternion::RotateY(angleY), RotateSpeed * deltaTime);
	}

	// ダッシュ中かの判定
	const float moveSpeed{ PlayerInput::KeyDash() ? MoveSpeed::DashSpeed : MoveSpeed::DefaultSpeed };

	// モデル描画位置を移動
	m_playerPosition.moveBy(velocity * moveSpeed * deltaTime);
}

void PlayerCharacter::animationUpdate()
{
	// アニメーション用のタイマーをカウントアップ
	m_animationTimer += Scene::DeltaTime() * AnimationSpeed;

	// アニメーション配列を切替
	
	// 攻撃中でない
	if (!m_isAttacking)
	{
		// バッファが空でない
		if (!m_attackInputBuffer.empty())
		{
			m_animationArray = m_attackInputBuffer.front();
			m_attackInputBuffer.pop();

			m_animationTimer = 0;
			m_isAttacking = true;
		}
		else if (PlayerInput::KeyGuard())
		{
			m_animationArray = ModelAssets::GetInstance().guardAnimationArray;
		}
		else if (PlayerInput::GetMovementAxis().isZero())
		{
			m_animationArray = ModelAssets::GetInstance().idleAnimationArray;
		}
		else
		{
			m_animationArray = ModelAssets::GetInstance().walkAnimationArray;
		}
	}

	// 配列の要素数を超える時、リセット
	if (m_animationTimer >= m_animationArray.size())
	{
		m_animationTimer = 0;

		// 攻撃モーションも終了
		m_isAttacking = false;
	}
}

Vec3 PlayerCharacter::getPlayerPosition() const
{
	// 基本姿勢の当たり判定を返す
	return ModelAssets::GetInstance().mannequinCollider.movedBy(m_playerPosition).oriented(m_playerRotation).center;
}

Quaternion PlayerCharacter::getPlayerRotation() const
{
	return m_playerRotation;
}
