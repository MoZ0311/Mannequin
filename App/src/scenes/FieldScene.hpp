// FieldScene class

# pragma once

# include "../core/Config.hpp"
# include "../player/PlayerCharacter.hpp"
# include "../player/CameraController.hpp"
# include "../field/TrashGenerator.hpp"
# include "../util/EEfectDrawer.hpp"

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

	// 部屋の描画
	void drawRoom() const;

	// 光の設定
	void initLighting() const;

	// レンダーテクスチャ
	const MSRenderTexture m_renderTexture;

	// フィールドの見えない壁
	const Box fieldArea;

	// エフェクト
	Effect m_effect;

	// プレイヤー
	PlayerCharacter m_player;

	// カメラ
	BasicCamera3D m_camera;

	// カメラ操作クラス
	CameraController m_cameraController;

	// ゴミ生成クラス
	TrashGenerator m_trashGenerator;
};
