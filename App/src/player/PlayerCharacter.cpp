// PlayerCharacter class

# include "PlayerCharacter.hpp"
#include "../core/ModelAssets.hpp"

using namespace Config::Player;

PlayerCharacter::PlayerCharacter()
	: m_playerPosition{ 0.0, 0.0, 0.0 }
	, m_playerRotation{ 0, 0, 0, 0 }
	, m_animationArray{ ModelAssets::GetInstance().idleAnimationArray }
	, m_animationTimer{ 0.0 }
{

}

void PlayerCharacter::update(const double deltaTime, const Vec3& cameraForward)
{
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

	if (!velocity.isZero())
	{
		// Y軸回転角度を計算
		const double angleY{ Atan2(velocity.x, velocity.z) };
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
	if (PlayerInput::KeyGuard())
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

	// 配列の要素数を超える時、リセット
	if (m_animationTimer >= m_animationArray.size())
	{
		m_animationTimer = 0;
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
