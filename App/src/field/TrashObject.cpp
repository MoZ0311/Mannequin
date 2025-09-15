// TrashObject class

# include "TrashObject.hpp"

TrashObject::TrashObject(const Vec3& position, const Model& model, const OrientedBox& collider)
	: m_playerOutsidecollider{ collider }
	, m_position{ position }
	, m_rotation{ Random(360_deg) }
	, m_model{ model }
{

}

void TrashObject::update(const double dettaTime)
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

void TrashObject::draw() const
{
	m_model.draw(m_position, Quaternion::RotateY(m_rotation));
}

const bool TrashObject::isCollidedPlayer() const
{
	return m_model.boundingBox().movedBy(m_position).intersects(m_playerOutsidecollider);
}
