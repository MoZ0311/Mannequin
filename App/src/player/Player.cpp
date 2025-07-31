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
	: m_velocity{ 0, 0, 0 }
	, m_sphere{ { 0, 0, 0 }, 1.0 }
{

}

void Player::update(const double& deltaTime, const Vec3& forwardVector)
{
	const Vec2 inputVector2D = PlayerInput::GetInputAxis();

	const Vec3 rightVector{ -forwardVector.cross(Vec3::Up()).normalized() };

	m_velocity = inputVector2D.y * forwardVector + inputVector2D.x * rightVector;
	m_sphere.moveBy(m_velocity * 10 * deltaTime);
}

void Player::draw() const
{
	m_sphere.draw();

	Print << U"Hello";
}
