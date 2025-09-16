// TitleScene class

# include "TitleScene.hpp"

using namespace Config::Scene;

TitleScene::TitleScene(const InitData& init)
	: IScene{ init }
	, m_backgroundImage{ TextureAsset(Assets::Title).resized(Scene::Size()) }
	, m_startButton{
		Arg::center = Components::TitleButtonPoint,
		Components::ButtonSize,
		Components::ButtonRoundness
	}
	, m_exitButton{ m_startButton.movedBy(Components::ButtonOffset) }
	, m_startTransition{ Components::ButtonTransition }
	, m_exitTransition{ Components::ButtonTransition }
	, m_currentSelectingButton{ SelectingButton::None }
	, m_usingGamePad{ false }
{

}

void TitleScene::update()
{
	if (PlayerInput::KeyUpper())
	{
		m_currentSelectingButton = SelectingButton::Start;
		m_usingGamePad = true;
	}
	else if (PlayerInput::KeyLower())
	{
		m_currentSelectingButton = SelectingButton::Exit;
		m_usingGamePad = true;
	}

	if (m_usingGamePad)
	{
		Cursor::RequestStyle(CursorStyle::Hidden);

		if (!Cursor::DeltaRaw().isZero())
		{
			m_usingGamePad = false;
		}
	}
	else
	{
		const bool onStart{ m_startButton.mouseOver() };
		const bool onExit{ m_exitButton.mouseOver() };

		if (onStart || onExit)
		{
			Cursor::RequestStyle(CursorStyle::Hand);
			if (onStart)
			{
				m_currentSelectingButton = SelectingButton::Start;
			}
			else if (onExit)
			{
				m_currentSelectingButton = SelectingButton::Exit;
			}
		}
		else
		{
			m_currentSelectingButton = SelectingButton::None;
		}
	}
	
	m_startTransition.update(m_currentSelectingButton == SelectingButton::Start);
	m_exitTransition.update(m_currentSelectingButton == SelectingButton::Exit);

	if (PlayerInput::KeyConfirm())
	{
		switch (m_currentSelectingButton)
		{
		case SelectingButton::Start:
			AudioAsset(Assets::Select).playOneShot();
			changeScene(State::Field, ChangeDuration);
			break;

		case SelectingButton::Exit:
			System::Exit();
			break;

		default:
			break;
		}
	}
}

void TitleScene::draw() const
{
	// 背景の描画
	m_backgroundImage.drawAt(Scene::CenterF());

	// Startボタンの描画
	m_startButton.draw(ColorF{ 1.0, m_startTransition.value() }).drawFrame(Components::ButtonThickness);
	FontAsset(Assets::Makinas)(U"START").drawAt(m_startButton.center(), Components::ButtonTextCollor);

	// Exitボタンの描画
	m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(Components::ButtonThickness);
	FontAsset(Assets::Makinas)(U"EXIT").drawAt(m_exitButton.center(), Components::ButtonTextCollor);
}
