// UnitSword class

#include "UnitSword.hpp"

UnitSword::UnitSword()
{
	m_attackRangeRadius = 2.0f;
	m_moveRangeRadius = 4.0f;

	m_maxHp = 50;
	m_currentHp = m_maxHp;

	m_unitName = U"剣士";
}
