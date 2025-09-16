// ClearScene class

# include "ClearScene.hpp"

using namespace Config::Scene;

ClearScene::ClearScene(const InitData& init)
	: IScene{ init }
	, m_backgroundImage{ TextureAsset(Assets::Clear).resized(Scene::Size()) }
	, m_retryButton{
		Arg::center = Components::OverButtonPoint,
		Components::ButtonSize,
		Components::ButtonRoundness
	}
	, m_exitButton{ m_retryButton.movedBy(Components::ButtonOffset) }
	, m_retryTransition{ Components::ButtonTransition }
	, m_exitTransition{ Components::ButtonTransition }
	, m_currentSelectingButton{ SelectingButton::None }
	, m_usingGamePad{ false }
{

}

// 更新処理
void ClearScene::update()
{
	if (PlayerInput::KeyUpper())
	{
		m_currentSelectingButton = SelectingButton::Retry;
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
		const bool onStart{ m_retryButton.mouseOver() };
		const bool onExit{ m_exitButton.mouseOver() };

		if (onStart || onExit)
		{
			Cursor::RequestStyle(CursorStyle::Hand);
			if (onStart)
			{
				m_currentSelectingButton = SelectingButton::Retry;
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

	m_retryTransition.update(m_currentSelectingButton == SelectingButton::Retry);
	m_exitTransition.update(m_currentSelectingButton == SelectingButton::Exit);

	if (PlayerInput::KeyConfirm())
	{
		switch (m_currentSelectingButton)
		{
		case SelectingButton::Retry:
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

// 描画処理
void ClearScene::draw() const
{
	// 背景の描画
	m_backgroundImage.drawAt(Scene::CenterF());

	// Startボタンの描画
	m_retryButton.draw(ColorF{ 1.0, m_retryTransition.value() }).drawFrame(Components::ButtonThickness);
	FontAsset(Assets::Makinas)(U"RETRY").drawAt(m_retryButton.center(), Components::ButtonTextCollor);

	// Exitボタンの描画
	m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(Components::ButtonThickness);
	FontAsset(Assets::Makinas)(U"EXIT").drawAt(m_exitButton.center(), Components::ButtonTextCollor);
}
