// TitleScene class

# include "TitleScene.hpp"

using namespace Config::Scene;

TitleScene::TitleScene(const InitData& init)
	: IScene{ init }
	, m_startButton{
		Arg::center = Components::TitleButtonPoint,
		Components::ButtonSize,
		Components::ButtonRoundness
	}
	, m_exitButton{ m_startButton.movedBy(Components::ButtonOffset) }
	, m_startTransition{ Components::ButtonTransition }
	, m_exitTransition{ Components::ButtonTransition }
{

}

void TitleScene::update()
{
	const bool onStart{ m_startButton.mouseOver() };
	const bool onExit{ m_exitButton.mouseOver() };

	m_startTransition.update(onStart);
	m_exitTransition.update(onExit);

	if (onStart || onExit)
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (m_startButton.leftClicked())
	{
		changeScene(State::Field, ChangeDuration);
	}
	else if (m_exitButton.leftClicked())
	{
		System::Exit();
	}
}

void TitleScene::draw() const
{
	// 背景の描画
	TextureRegion title{ TextureAsset(Assets::Title).resized(Scene::Size()) };
	title.drawAt(Scene::CenterF());

	// Startボタンの描画
	m_startButton.draw(ColorF{ 1.0, m_startTransition.value() }).drawFrame(Components::ButtonThickness);
	FontAsset(Assets::Makinas)(U"START").drawAt(m_startButton.center(), Components::ButtonTextCollor);

	// Exitボタンの描画
	m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(Components::ButtonThickness);
	FontAsset(Assets::Makinas)(U"EXIT").drawAt(m_exitButton.center(), Components::ButtonTextCollor);
}
