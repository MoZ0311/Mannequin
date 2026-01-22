// UIDrawer class

# include "UIDrawer.hpp"

using namespace UI;

UIDrawer::UIDrawer()
	: m_characterStatus{ Scene::Rect().bl() - StatusWindowPoint, StatusWindowSize }
	, m_score{ 0 }
{

}

UIDrawer::~UIDrawer()
{

}

void UIDrawer::update(const uint8 deletedCount)
{
	m_score = deletedCount;
}

void UIDrawer::draw() const
{
	m_characterStatus.rounded(0, WindowRoundness, 0, 0).draw(ColorF{0.0, 0.0, 0.0, 0.9});

	const String score{ U"片付けたゴミ: " + Format(m_score) };
	FontAsset(Assets::Makinas)(score).drawAt(FontSize, m_characterStatus.center());
}
