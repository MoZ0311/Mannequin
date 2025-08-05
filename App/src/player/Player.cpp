// Player class

# include "Player.hpp"

using namespace Config::Player;

Vec3 Player::GetPlayerPosition() const
{
	return m_siv3dkun.boundingBox().movedBy(m_playerPosition).center;
}

Player::Player()
	: m_playerPosition{ 0.0, 0.0, 0.0 }
	, m_playerRotation{ 0, 0, 0, 0 }
	, m_siv3dkun{ U"example/obj/siv3d-kun.obj" }
	, m_attackRing{ m_playerPosition.x, m_playerPosition.z, 2.0 }
{
	Model::RegisterDiffuseTextures(m_siv3dkun, TextureDesc::MippedSRGB);
}

void Player::update(const double deltaTime, const Vec3 cameraForward)
{
	// 平面移動ベクトル(x : 左右, y : 前後)
	const Vec2 movementVector2D{ PlayerInput::GetMovementAxis() };

	// カメラの向きを基準にした右向きベクトル
	const Vec3 rightVector{ -cameraForward.cross(Vec3::Up()).normalized() };

	// 空間移動ベクトル
	const Vec3 velocity{ movementVector2D.y * cameraForward + movementVector2D.x * rightVector };

    if (!velocity.isZero())
    {
		// Y軸回転角度を計算
		const double angleY{ Atan2(velocity.x, velocity.z) };
		m_playerRotation = m_playerRotation.slerp(Quaternion::RotateY(angleY), RotateSpeed * deltaTime);
    }

	const double dashSpeed{ PlayerInput::KeyDash() ? 2.5 : 1.0 };
	m_playerPosition.moveBy(velocity * MoveSpeed * dashSpeed * deltaTime);
}

void Player::draw() const
{
	m_siv3dkun.draw(m_playerPosition, m_playerRotation);
}
