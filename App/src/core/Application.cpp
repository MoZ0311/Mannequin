// Application class

# include "Application.hpp"

using namespace Config;
using namespace Config::Scene;

Application::Application()
	: m_sceneManager{}
{
	// ウィンドウサイズの設定
	Window::Resize(ScreenSize);

	// 各シーン登録
	addScenes();

	// 最初のシーンを設定
	m_sceneManager.init(State::Title, ChangeDuration);
}

bool Application::run()
{
	return m_sceneManager.update();
}

void Application::addScenes()
{
	m_sceneManager.add<TitleScene>(State::Title);	// タイトルシーン
	m_sceneManager.add<FieldScene>(State::Field);	// フィールド
	m_sceneManager.add<OverScene>(State::Over);		// ゲームオーバー
	m_sceneManager.add<ClearScene>(State::Clear);	// クリア
}
