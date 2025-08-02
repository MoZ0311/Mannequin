// FieldScene class

# pragma once

# include "../core/Config.hpp"
# include "../player/Player.hpp"
# include "../player/CameraController.hpp"

class FieldScene : public Config::Scene::SceneApp::Scene
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
	const MSRenderTexture m_renderTexture;

	// プレイヤー
	Player& m_player;

	// カメラ
	BasicCamera3D m_camera;

	// カメラ操作クラス
	CameraController m_cameraController;	
};
