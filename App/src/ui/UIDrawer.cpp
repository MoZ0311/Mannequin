// UIDrawer class

# include "../ui/UIDrawer.hpp"

using namespace UI;

UIDrawer::UIDrawer()
	: m_characterStatus{ Scene::Rect().bl() - StatusWindowPoint, StatusWindowSize }
	, m_unitName{}
	, m_maxUnitHp{ 0 }
	, m_currentUnitHp{ 0 }
{

}

UIDrawer::~UIDrawer()
{

}

void UIDrawer::update(const UnitBase* unitBase)
{
	m_maxUnitHp = unitBase->getMaxHp();
	m_currentUnitHp = unitBase->getCurrentHp();
}

void UIDrawer::draw() const
{
	m_characterStatus.rounded(0, WindowRoundness, 0, 0).draw(ColorF{0.0, 0.0, 0.0, 0.9});

	const String hitPoint{ Format(m_currentUnitHp) + U"/" + Format(m_currentUnitHp) };
	FontAsset(Assets::Makinas)(hitPoint).drawAt(m_characterStatus.center());
}
