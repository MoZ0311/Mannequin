// Application class

# pragma once

# include "../scenes/TitleScene.hpp"
# include "../scenes/FieldScene.hpp"
# include "../scenes/OverScene.hpp"
# include "../scenes/ClearScene.hpp"

class Application
{
public:

	// コンストラクタ
	Application();

	// アプリケーション実行
	bool run();

private:

	// シーンの登録処理
	void addScenes();

	// シーンマネージャー
	Config::Scene::SceneApp m_sceneManager;
};
