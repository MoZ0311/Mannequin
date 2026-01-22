// OverScene class

# pragma once

# include "../core/Config.hpp"
# include "../player/PlayerInput.hpp"

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

	enum class SelectingButton
	{
		None,
		Retry,
		Exit,
	};

	// 背景画像
	const TextureRegion m_backgroundImage;

	// RETRY ボタンの設定
	const RoundRect m_retryButton;
	Transition m_retryTransition;

	// EXIT ボタンの設定
	const RoundRect m_exitButton;
	Transition m_exitTransition;

	// 選択中のボタン
	SelectingButton m_currentSelectingButton;

	// ゲームパッドを使うか
	bool m_usingGamePad;
};
