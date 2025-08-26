// BattkeScene class

# include "BattleScene.hpp"

using namespace Config::Scene;
using namespace Config::Camera;

BattleScene::BattleScene(const InitData& init)
	: IScene{ init }
	, m_renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes }
	, m_camera{ m_renderTexture.size(), FOV::Wide, Vec3{ 10, 16, -32 } }
	, m_cameraController{ m_camera }
{

}

void BattleScene::update()
{

}

void BattleScene::draw() const
{
	// 3Dシーンにカメラを設定
	Graphics3D::SetCameraTransform(m_camera);

	// 3D描画
	{
		const ScopedRenderTarget3D target{ m_renderTexture.clear(Field::BackgroundColor.removeSRGBCurve()) };

		Plane{ 64 }.draw(TextureAsset(Assets::UV));

		// プレイヤーの描画
	}

	// 2Dに転送
	{
		Graphics3D::Flush();
		m_renderTexture.resolve();
		Shader::LinearToScreen(m_renderTexture);
	}
}
