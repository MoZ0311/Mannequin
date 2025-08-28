// OverScene class

#pragma once

# include "../core/Config.hpp"

class OverScene : public Config::Scene::SceneApp::Scene
{
public:

	// コンストラクタ
	OverScene(const InitData& init);

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

	// RETRY ボタンの設定
	const RoundRect m_retryButton;
	Transition m_retryTransition;

	// EXIT ボタンの設定
	const RoundRect m_exitButton;
	Transition m_exitTransition;
};
