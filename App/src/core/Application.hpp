// Application class

# pragma once

# include "../scenes/TitleScene.hpp"
# include "../scenes/FieldScene.hpp"

class Application
{
public:

	// コンストラクタ
	Application();

	// デストラクタ
	~Application();

	// アプリケーション実行
	bool run();

private:

	// シーンマネージャー
	Config::Scene::App m_sceneManager;
};
