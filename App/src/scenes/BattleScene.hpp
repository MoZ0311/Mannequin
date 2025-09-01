// BattleScene class

# pragma once

# include "../core/Config.hpp"
# include "../player/CameraController.hpp"
# include "../unit/UnitSword.hpp"

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

	// 自軍ユニット
	// Array<Player*> u;

	// カメラ
	BasicCamera3D m_camera;

	// カメラ操作クラス
	CameraController m_cameraController;	
};
