// TrashObject class

# include "TrashObject.hpp"

TrashObject::TrashObject(const Vec3& position, const Model& model, const PlayerCharacter& instance)
	: m_playerInstance{ instance }
	, m_position{ position }
	, m_rotation{ Random(360_deg) }
	, m_model{ model }
{

}

void TrashObject::update(const double dettaTime)
{
	if (isDamaged())
	{
		const Vec3 moveVector{ Vec3::Forward() * m_playerInstance.getPlayerRotation() };
		m_position.moveBy(moveVector);
	}
	else
	{
		if (m_position.y > 0)
		{
			m_position.y -= dettaTime * 5;
		}
		else
		{
			m_position.y = 0;
		}
	}
}

void TrashObject::draw() const
{
	m_model.draw(m_position, Quaternion::RotateY(m_rotation));
}

const bool TrashObject::isCollidedPlayer() const
{
	return m_model.boundingBox().movedBy(m_position).intersects(m_playerInstance.getOutsideCollider());
}

const bool TrashObject::isDamaged() const
{
	return m_model.boundingBox().movedBy(m_position).intersects(m_playerInstance.getAttackCollider());
}
