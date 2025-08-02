// Player class

# include "Player.hpp"

std::unique_ptr<Player> Player::instance = nullptr;

Player& Player::GetInstance()
{
	if (!instance)
	{
		instance.reset(new Player());
	}
	return *instance;
}

Vec3 Player::GetPlayerPosition() const
{
	return m_sphere.center;
}

Player::Player()
	: m_moveSpeed{ 10.0 }
	, m_sphere{ { 0, 0, 0 }, 1.0 }
{

}

void Player::update(const double deltaTime, const Vec3 forwardVector)
{
	// 平面移動ベクトル(x : 左右, y : 前後)
	const Vec2 movementVector2D{ PlayerInput::GetMovementAxis() };

	// カメラの向きを基準にした右向きベクトル
	const Vec3 rightVector{ -forwardVector.cross(Vec3::Up()).normalized() };

	// 空間移動ベクトル
	const Vec3 velocity{ movementVector2D.y * forwardVector + movementVector2D.x * rightVector };

	m_sphere.moveBy(velocity * m_moveSpeed * deltaTime);
}

void Player::draw() const
{
	m_sphere.draw();
}
