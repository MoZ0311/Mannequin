// BattleScene class

# pragma once

# include "../core/Config.hpp"
# include "../player/CameraController.hpp"
# include "../ui/UIDrawer.hpp"
# include "../unit/UnitManager.hpp"
# include "../unit/UnitSword.hpp"

class BattleScene : public Config::Scene::SceneApp::Scene
{
public:

	// コンストラクタ
	BattleScene(const InitData& init);

	// デストラクタ
	~BattleScene();

	// 更新処理
	void update() override;

	// 描画処理
	void draw() const override;

private:

	// レンダーテクスチャ
	const MSRenderTexture m_renderTexture;

	// UI描画クラス
	UIDrawer m_uiDrawer;

	// ユニットの配列管理
	UnitManager* m_unitManager;

	// カメラ
	BasicCamera3D m_camera;

	// カメラ操作クラス
	CameraController m_cameraController;	
};
