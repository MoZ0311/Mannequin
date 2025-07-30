// Player class

# include "Player.hpp"

Player* Player::instance = nullptr;

void Player::Init()
{
	if (!instance)
	{
		instance = new Player();
	}
}

void Player::Release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

Player* Player::GetInstance()
{
	return instance;
}

Vec3 Player::GetPlayerPosition() const
{
	return m_sphere.center;
}

Player::Player()
	: m_moveSpeed{ 5.0 }
	, m_sphere{ { 0, 0, 0 }, 1.0 }
{

}

Player::~Player()
{

}

void Player::update(double& deltaTime)
{
	m_sphere.moveBy(PlayerInput::GetInputVector() * m_moveSpeed * deltaTime);
}

void Player::draw() const
{
	m_sphere.draw();
}
