// TrashGenerator class

# include "TrashGenerator.hpp"
# include "../core/ModelAssets.hpp"

TrashGenerator::TrashGenerator()
	: m_generateTimer{ 0.0 }
	, m_trashObjectArray{}
{

}

void TrashGenerator::update(const double deltaTime, const Box& fieldArea)
{
	m_generateTimer -= deltaTime;
	if (m_generateTimer <= 0)
	{
		m_generateTimer = 0.2;
		generateTrash(fieldArea);
	}

	for (const auto& trash : m_trashObjectArray)
	{
		trash->update(deltaTime);
	}
}

void TrashGenerator::draw() const
{
	for (const auto& trash : m_trashObjectArray)
	{
		trash->draw();
	}
}

void TrashGenerator::generateTrash(const Box& fieldArea)
{
	// ランダムな平面座標を生成
	Vec3 randomPosition{ RandomVec3(fieldArea) };
	randomPosition.y = 8;

	m_trashObjectArray.push_back(std::make_unique<TrashObject>(randomPosition, ModelAssets::GetInstance().qpKowa));
}
