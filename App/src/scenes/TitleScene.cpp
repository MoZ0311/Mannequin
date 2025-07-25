// TitleScene class

#include "TitleScene.hpp"

TitleScene::TitleScene(const InitData& init)
	: IScene{ init }
	, startButton{
		Arg::center = Scene::Center().moveBy(Components::ButtonOffset * 2),
		Components::ButtonSize
	}
	, exitButton{ startButton.movedBy(Components::ButtonOffset) }
	, startTransition{ Components::ButtonTransition }
	, exitTransition{ Components::ButtonTransition }
{

}

void TitleScene::update()
{
	const bool onStart = startButton.mouseOver();
	const bool onExit = exitButton.mouseOver();

	startTransition.update(onStart);
	exitTransition.update(onExit);

	if (onStart || onExit)
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (startButton.leftClicked())
	{
		changeScene(State::Field, SceneConfig::ChangeDuration);
	}
	else if (exitButton.leftClicked())
	{
		System::Exit();
	}
}

void TitleScene::draw() const
{
	// Startボタンの描画
	startButton.draw(ColorF{ 1.0, startTransition.value() }).drawFrame(2);
	//FontAsset(FONT_MAKINAS)(U"復興").drawAt(startButton.center(), ColorF{ 0.25 });

	// Exitボタンの描画
	exitButton.draw(ColorF{ 1.0, exitTransition.value() }).drawFrame(2);
	//FontAsset(FONT_MAKINAS)(U"バトル").drawAt(battleButton.center(), ColorF{ 0.25 });
}
