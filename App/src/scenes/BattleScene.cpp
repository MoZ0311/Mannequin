// BattkeScene class

# include "BattleScene.hpp"

using namespace Config::Scene;
using namespace Config::Camera;

BattleScene::BattleScene(const InitData& init)
	: IScene{ init }
	, m_renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes }
	, m_uiDrawer{}
	, m_unitManager{ UnitManager::GetInstance() }
	, m_camera{ m_renderTexture.size(), FOV::Narrow, Vec3{ 10, 16, -32 } }
	, m_cameraController{ m_camera }
{

}

BattleScene::~BattleScene()
{
	// シングルトンクラスの解放
	UnitManager::Release();
}

void BattleScene::update()
{
	// シーンにおける前フレームからの経過時間
	const double deltaTime{ Scene::DeltaTime() };

	// マウスカーソル設定
	Cursor::RequestStyle(CursorStyle::Hidden);
	Cursor::SetPos(Scene::Center());

	// ユニット管理クラスの更新
	m_unitManager->update(deltaTime, m_cameraController.getCameraForward());

	// 選択中のユニットの情報を取得
	const uint8 index{ m_unitManager->getUnitIndex() };
	const UnitBase* unit{ m_unitManager->getUnitData(index) };

	// UI描画の更新
	m_uiDrawer.update(unit);

	// カメラの更新
	m_cameraController.update(deltaTime, unit->getPlayerPosition(), unit->getPlayerRotation());
}

void BattleScene::draw() const
{
	// 3Dシーンにカメラを設定
	Graphics3D::SetCameraTransform(m_camera);

	// 3D描画
	{
		const ScopedRenderTarget3D target{ m_renderTexture.clear(Field::BackgroundColor.removeSRGBCurve()) };
		const ScopedRenderStates3D blend{ BlendState::OpaqueAlphaToCoverage };

		Plane{ 64 }.draw(TextureAsset(Assets::UV));

		// ユニットの描画
		m_unitManager->draw();
	}

	// 2Dに転送
	{
		Graphics3D::Flush();
		m_renderTexture.resolve();
		Shader::LinearToScreen(m_renderTexture);
	}

	// UI描画
	m_uiDrawer.draw();
}
