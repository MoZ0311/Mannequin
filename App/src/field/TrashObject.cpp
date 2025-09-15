// TrashObject class

# include "TrashObject.hpp"

TrashObject::TrashObject(const Vec3& position, const Model& model)
	: m_position{ position }
	, m_model{ model }
{

}

// 更新処理
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

// 描画処理
void TrashObject::draw() const
{
	m_model.draw(m_position);
}
