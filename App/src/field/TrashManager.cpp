// TrashManager class

# include "TrashManager.hpp"

TrashManager::TrashManager(const Box& fieldArea, const PlayerCharacter& instance)
	: maxGenerateCount{ 20 }
	, m_generateInterval{ 0.5 }
	, m_fieldArea{ fieldArea }
	, m_playerInstance{ instance }
	, m_isCollided{ false }
	, m_generateTimer{ 0.0 }
	, m_deletedTrashCount{ 0 }
	, m_trashObjectArray{}
{

}

void TrashManager::update(const double deltaTime)
{
	m_generateTimer -= deltaTime;
	if (m_trashObjectArray.size() < maxGenerateCount && m_generateTimer <= 0)
	{
		m_generateTimer = m_generateInterval;
		generateTrash();
	}

	// イテレーターを回して落ちたオブジェクトを破棄
	for (auto it{ m_trashObjectArray.begin() }; it != m_trashObjectArray.end();)
	{
		if (it->get()->isGrounded())
		{
			it = m_trashObjectArray.erase(it);
		}
		else
		{
			if (it->get()->isOutside())
			{
				++m_deletedTrashCount;
			}
			++it;
		}
	}

	// 配列を走査して全要素を更新
	for (const auto& trash : m_trashObjectArray)
	{
		trash->update(deltaTime);
	}

	// プレイヤーに触れたオブジェクトがあったか
	m_isCollided = m_trashObjectArray.any([](const auto& trash) {
		return trash.get()->isCollidedPlayer();
	});

	// プレイヤーに攻撃されたオブジェクトがあったか
	m_isDamaged = m_trashObjectArray.any([](const auto& trash) {
		return trash.get()->getIsDamaged();
	});
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

	// unique_ptrとして配列に追加
	m_trashObjectArray.push_back(std::make_unique<TrashObject>(randomPosition, ModelAssets::GetInstance().qpKowa, m_playerInstance, m_fieldArea));
}

const bool TrashManager::isCollidedPlayer() const
{
	return m_isCollided;
}

const bool TrashManager::isDamaged() const
{
	return m_isDamaged;
}

const uint8 TrashManager::getDeletedTrashCount() const
{
	return m_deletedTrashCount;
}
