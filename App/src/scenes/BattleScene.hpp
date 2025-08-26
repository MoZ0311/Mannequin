// BattleScene class

# pragma once

# include "../core/Config.hpp"
# include "../player/CameraController.hpp"

class BattleScene : public Config::Scene::SceneApp::Scene
{
public:

	// コンストラクタ
	BattleScene(const InitData& init);

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

	// レンダーテクスチャ
	const MSRenderTexture m_renderTexture;

	// プレイヤー
	// Player m_player;

	// カメラ
	BasicCamera3D m_camera;

	// カメラ操作クラス
	CameraController m_cameraController;	
};
