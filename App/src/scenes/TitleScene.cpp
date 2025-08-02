// TitleScene class

# include "TitleScene.hpp"

using namespace Config::Scene;

TitleScene::TitleScene(const InitData& init)
	: IScene{ init }
	, m_startButton{
		Arg::center = Scene::Center().moveBy(Components::ButtonOffset * 2),
		Components::ButtonSize
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
	// Startボタンの描画
	m_startButton.draw(ColorF{ 1.0, m_startTransition.value() }).drawFrame(2);
	//FontAsset(FONT_MAKINAS)(U"復興").drawAt(startButton.center(), ColorF{ 0.25 });

	// Exitボタンの描画
	m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);
	//FontAsset(FONT_MAKINAS)(U"バトル").drawAt(battleButton.center(), ColorF{ 0.25 });
}
