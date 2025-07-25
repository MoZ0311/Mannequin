// FieldScene class

#pragma once

#include "../core/Constants.hpp"

using namespace SceneConfig;

class FieldScene : public App::Scene
{
public:

	// コンストラクタ
	FieldScene(const InitData& init);

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

	// 光の設定
	void initLighting() const;

	// レンダーテクスチャ
	const MSRenderTexture renderTexture;

	// カメラ
	DebugCamera3D cam;
};
