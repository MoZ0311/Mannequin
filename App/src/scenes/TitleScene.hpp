// TitleScene class

#pragma once

#include "../core/Constants.hpp"

using namespace SceneConfig;

class TitleScene : public App::Scene
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
	const Rect startButton;
	Transition startTransition;

	// EXIT ボタンの設定
	const Rect exitButton;
	Transition exitTransition;
};
