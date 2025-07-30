// FieldScene class

# pragma once

# include "../core/Config.hpp"
# include "../player/Player.hpp"

using namespace Config::Scene;

class FieldScene : public App::Scene
{
public:

	// コンストラクタ
	FieldScene(const InitData& init);

	// デストラクタ
	~FieldScene();

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

	// 光の設定
	void initLighting() const;

	// レンダーテクスチャ
	const MSRenderTexture m_renderTexture;

	// カメラ
	BasicCamera3D m_camera;
};
