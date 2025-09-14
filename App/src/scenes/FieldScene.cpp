// FieldScene class

# include "FieldScene.hpp"

using namespace Config::Scene;
using namespace Config::Camera;

FieldScene::FieldScene(const InitData& init)
	: IScene{ init }
	, m_renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes }
	, m_effect{}
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
	m_cameraController.update(deltaTime, m_player.getPlayerPosition(), m_player.getPlayerRotation());

	// debug
	if (KeyEnter.down())
	{
		changeScene(State::Over, ChangeDuration);
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

		Plane{ Vec3{ 0.0, -16.0, 0.0 }, 64 }.draw(TextureAsset(Assets::Floor));	// ゆか
		Plane{ Vec3{ 0.0, 16.0, -32.0 }, 64 }.draw(Quaternion::RotateX(90_deg), TextureAsset(Assets::Floor));	// 手前の壁
		Plane{ Vec3{ 0.0, 16.0, 32.0 }, 64 }.draw(Quaternion::RotateX(-90_deg), TextureAsset(Assets::Floor));	// 奥の壁
		Plane{ Vec3{ -32.0, 16.0, 0.0 }, 64 }.draw(Quaternion::RotateZ(90_deg), TextureAsset(Assets::Floor));	// 左の壁
		Plane{ Vec3{ 32.0, 16.0, 0.0 }, 64 }.draw(Quaternion::RotateZ(-90_deg), TextureAsset(Assets::Floor));	// 右の壁


		// プレイヤーの描画
		m_player.draw();

		Box::FromPoints(Vec3{ -16, 0, -16 }, Vec3{ 16, -2, 16 }).draw(TextureAsset(Assets::Wood));	// 机
	}

	// 2Dに転送
	{
		Graphics3D::Flush();
		m_renderTexture.resolve();
		Shader::LinearToScreen(m_renderTexture);
	}

	if (MouseL.down())
	{
		const Vec2& effectPostion{ Util::WorldToScreenPosition(m_player.getPlayerPosition(), m_camera) };
		m_effect.add<BubbleEffect>(effectPostion);
	}

	m_effect.update();
}

void FieldScene::initLighting() const
{
	//Graphics3D::SetGlobalAmbientColor(ColorF{ 0.3 });	// 環境光
	Graphics3D::SetSunColor(ColorF{ 1.0 });				// 平行光
	Graphics3D::SetSunDirection(Vec3{ 0.25, 0.75, -0.6 }.normalized());
}
