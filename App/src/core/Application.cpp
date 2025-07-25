// Application class

#include "Application.hpp"

Application::Application()
	: manager{}
{
	manager.add<TitleScene>(State::Title);
	manager.add<FieldScene>(State::Field);

	// 最初のシーンを設定
	manager.init(State::Title, SceneConfig::ChangeDuration);
}

Application::~Application()
{

}

bool Application::run()
{
	return manager.update();
}
