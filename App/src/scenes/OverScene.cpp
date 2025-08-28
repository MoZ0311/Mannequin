// OverScene class

# include "OverScene.hpp"

using namespace Config::Scene;

OverScene::OverScene(const InitData& init)
	: IScene{ init }
	, m_retryButton{
		Arg::center = Components::OverButtonPoint,
		Components::ButtonSize,
		Components::ButtonRoundness
	}
	, m_exitButton{ m_retryButton.movedBy(Components::ButtonOffset) }
	, m_retryTransition{ Components::ButtonTransition }
	, m_exitTransition{ Components::ButtonTransition }
{

}

// 更新処理
void OverScene::update()
{
	const bool onStart{ m_retryButton.mouseOver() };
	const bool onExit{ m_exitButton.mouseOver() };

	m_retryTransition.update(onStart);
	m_exitTransition.update(onExit);

	if (onStart || onExit)
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (m_retryButton.leftClicked())
	{
		changeScene(State::Field, ChangeDuration);
	}
	else if (m_exitButton.leftClicked())
	{
		System::Exit();
	}
}

// 描画処理
void OverScene::draw() const
{
	// 背景の描画
	TextureRegion title{ TextureAsset(Assets::Over).resized(Scene::Size()) };
	title.drawAt(Scene::CenterF());

	// Startボタンの描画
	m_retryButton.draw(ColorF{ 1.0, m_retryTransition.value() }).drawFrame(Components::ButtonThickness);
	FontAsset(Assets::Makinas)(U"RETRY").drawAt(m_retryButton.center(), Components::ButtonTextCollor);

	// Exitボタンの描画
	m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(Components::ButtonThickness);
	FontAsset(Assets::Makinas)(U"EXIT").drawAt(m_exitButton.center(), Components::ButtonTextCollor);
}
