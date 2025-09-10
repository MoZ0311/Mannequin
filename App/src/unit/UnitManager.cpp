// UnitManager class

# include "UnitManager.hpp"

UnitManager* UnitManager::instance = nullptr;

UnitManager::UnitManager()
	: m_playerUnitArray{}
	, m_enemyUnitArray{}
	, m_allUnitArray{}
	, m_selectedUnitIndex{ 0 }
{
	createUnits();
}

UnitManager::~UnitManager()
{
	resetUnitArray();
}

UnitManager* UnitManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new UnitManager();
	}
	return instance;
}

void UnitManager::Release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void UnitManager::update(double deltaTime, Vec3 cameraForward)
{
	if (KeyEnter.down())
	{
		m_selectedUnitIndex++;
		if (m_selectedUnitIndex >= m_allUnitArray.size())
		{
			m_selectedUnitIndex = 0;
		}
	}

	m_allUnitArray[m_selectedUnitIndex]->update(deltaTime, cameraForward);
}

void UnitManager::draw() const
{
	for (UnitBase* unit : m_allUnitArray)
	{
		unit->draw();
	}

	m_allUnitArray[m_selectedUnitIndex]->drawUI();
}

UnitBase* UnitManager::getUnitData(uint8 index) const
{
	return m_allUnitArray[index];
}

uint8 UnitManager::getUnitIndex() const
{
	return m_selectedUnitIndex;
}

void UnitManager::resetUnitArray()
{
	for (PlayerCharacter* unit : m_allUnitArray)
	{
		delete unit;
		unit = nullptr;
	}
	m_allUnitArray.clear();
}

void UnitManager::createUnits()
{
	// 変数の用意
	UnitBase* unitInstance{ nullptr };

	unitInstance = new UnitSword();

	m_allUnitArray.push_back(unitInstance);

	unitInstance = new UnitArcher();

	m_allUnitArray.push_back(unitInstance);
}
