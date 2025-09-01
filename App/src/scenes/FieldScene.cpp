// FieldScene class

# include "FieldScene.hpp"

using namespace Config::Scene;
using namespace Config::Camera;

FieldScene::FieldScene(const InitData& init)
	: IScene{ init }
	, m_renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes }
	, m_camera{ m_renderTexture.size(), FOV::Narrow }
	, m_cameraController{ m_camera }
	, m_player{}
{
	initLighting();

	// マウスカーソル設定
	Cursor::RequestStyle(CursorStyle::Hidden);
	Cursor::SetPos(Scene::Center());
}

void FieldScene::update()
{
	// シーンにおける前フレームからの経過時間
	const double deltaTime{ Scene::DeltaTime() };

	// マウスカーソル設定
	Cursor::RequestStyle(CursorStyle::Hidden);
	Cursor::SetPos(Scene::Center());

	// プレイヤーの更新
	m_player.update(deltaTime, m_cameraController.getCameraForward());

	// カメラの更新
	m_cameraController.update(deltaTime, m_player.GetPlayerPosition(), m_player.GetPlayerRotation());

	// debug
	if (KeyEnter.down())
	{
		changeScene(State::Battle, ChangeDuration);
	}
}

void FieldScene::draw() const
{
	// 3Dシーンにカメラを設定
	Graphics3D::SetCameraTransform(m_camera);

	// 3D描画
	{
		const ScopedRenderTarget3D target{ m_renderTexture.clear(Field::BackgroundColor.removeSRGBCurve()) };
		const ScopedRenderStates3D blend{ BlendState::OpaqueAlphaToCoverage };

		Plane{ 64 }.draw(TextureAsset(Assets::UV));

		// プレイヤーの描画
		m_player.draw();
	}

	// 2Dに転送
	{
		Graphics3D::Flush();
		m_renderTexture.resolve();
		Shader::LinearToScreen(m_renderTexture);
	}
}

void FieldScene::initLighting() const
{
	Graphics3D::SetGlobalAmbientColor(ColorF{ 0.1 });	// 環境光
	Graphics3D::SetSunColor(ColorF{ 1.0 });				// 平行光
	Graphics3D::SetSunDirection(Vec3{ 0.3, 1.0, 0.2 }.normalized());
}
