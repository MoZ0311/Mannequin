// TitleScene class

# pragma once

# include "../core/Config.hpp"

class TitleScene : public Config::Scene::SceneApp::Scene
{
public:

	// コンストラクタ
	TitleScene(const InitData& init);

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

	// START ボタンの設定
	const RoundRect m_startButton;
	Transition m_startTransition;

	// EXIT ボタンの設定
	const RoundRect m_exitButton;
	Transition m_exitTransition;
};
