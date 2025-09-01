// PlayerCharacter class

# include "PlayerCharacter.hpp"

using namespace Config::Player;

Vec3 PlayerCharacter::GetPlayerPosition() const
{
	return m_siv3dkun.boundingBox().movedBy(m_playerPosition).center;
}

Quaternion  PlayerCharacter::GetPlayerRotation() const
{
	return m_playerRotation;
}

PlayerCharacter::PlayerCharacter()
	: m_playerPosition{ 0.0, 0.0, 0.0 }
	, m_playerRotation{ 0, 0, 0, 0 }
	, m_siv3dkun{ U"example/obj/siv3d-kun.obj" }
{
	Model::RegisterDiffuseTextures(m_siv3dkun, TextureDesc::MippedSRGB);
}

void PlayerCharacter::update(const double deltaTime, const Vec3 cameraForward)
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

	const float moveSpeed{ PlayerInput::KeyDash() ? MoveSpeed::DashSpeed : MoveSpeed::DefaultSpeed };
	m_playerPosition.moveBy(velocity * moveSpeed * deltaTime);
}

void PlayerCharacter::draw() const
{
	m_siv3dkun.draw(m_playerPosition, m_playerRotation);

	//Util::DrawDiscFrame(m_playerPosition, 2);

	//Disc ring{ Vec3{ m_playerPosition.x, 0.0001, m_playerPosition.z }, 2 };
	//ring.draw(ColorF{ 0, 1, 1, 0.3 }.removeSRGBCurve());
}
