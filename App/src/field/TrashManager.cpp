// TrashManager class

# include "TrashManager.hpp"

TrashManager::TrashManager(const Box& fieldArea)
	: m_fieldArea{ fieldArea }
	, m_generateTimer{ 0.0 }
	, m_trashObjectArray{}
{

}

void TrashManager::update(const double deltaTime)
{
	m_generateTimer -= deltaTime;
	if (m_trashObjectArray.size() < 5 && m_generateTimer <= 0)
	{
		m_generateTimer = 3.0;
		generateTrash();
	}

	// 配列を走査して全要素を更新
	for (const auto& trash : m_trashObjectArray)
	{
		trash->update(deltaTime);
	}
}

void TrashManager::draw() const
{
	// 配列を走査して全要素を描画
	for (const auto& trash : m_trashObjectArray)
	{
		trash->draw();
	}
}

void TrashManager::generateTrash()
{
	// ランダムな平面座標を生成
	Vec3 randomPosition{ RandomVec3(m_fieldArea) };
	randomPosition.y = 8;

	m_trashObjectArray.push_back(std::make_unique<TrashObject>(randomPosition, ModelAssets::GetInstance().qpKowa));
}
