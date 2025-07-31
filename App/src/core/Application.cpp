// Application class

# include "Application.hpp"

Application::Application()
	: m_sceneManager{}
{
	// ウィンドウサイズの設定
	Window::Resize(Config::ScreenSize);

	m_sceneManager.add<TitleScene>(State::Title);
	m_sceneManager.add<FieldScene>(State::Field);

	// 最初のシーンを設定
	m_sceneManager.init(State::Title, Config::Scene::ChangeDuration);
}

bool Application::run()
{
	return m_sceneManager.update();
}
