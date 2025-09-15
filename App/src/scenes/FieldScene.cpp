// FieldScene class

# include "FieldScene.hpp"

using namespace Config::Scene;
using namespace Config::Camera;

FieldScene::FieldScene(const InitData& init)
	: IScene{ init }
	, m_fieldArea{ 32 }
	, m_renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes }
	, m_effect{}
	, m_player{ m_fieldArea }
	, m_camera{ m_renderTexture.size(), FOV::Narrow }
	, m_cameraController{ m_camera }
	, m_trashManager{ m_fieldArea }
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
	m_player.update(deltaTime, m_cameraController.getCameraForward(), m_trashManager.isCollidedPlayer());

	// カメラの更新
	m_cameraController.update(deltaTime, m_player.getPlayerPosition(), m_player.getPlayerRotation());

	// 生成クラスの更新
	m_trashManager.update(deltaTime, m_player.getOutsideCollider());

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

		drawRoom();

		// プレイヤーの描画
		m_player.draw();

		// その他3Dオブジェクトの描画
		m_trashManager.draw();
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

void FieldScene::drawRoom() const
{
	const float offset{ 13.0 };
	const float size{ 64.0 };

	Plane{ Vec3{ 0.0, offset - size / 2.0f, 0.0 }, size }.draw(TextureAsset(Assets::Floor));	// ゆか
	Plane{ Vec3{ 0.0, offset, size / 2.0f }, size }.draw(Quaternion::RotateX(-90_deg), TextureAsset(Assets::WallFront));	// 奥の壁
	Plane{ Vec3{ 0.0, offset, -size / 2.0f }, size }.draw(Quaternion::RotateX(-90_deg), TextureAsset(Assets::WallRear));	// 手前の壁
	Plane{ Vec3{ -size / 2.0f, offset, 0.0 }, size }.draw(Quaternion::RollPitchYaw(-90_deg, 90_deg, 0_deg), TextureAsset(Assets::WallLeft));	// 左の壁
	Plane{ Vec3{ size / 2.0f, offset, 0.0 }, size }.draw(Quaternion::RollPitchYaw(-90_deg, 90_deg, 0_deg), TextureAsset(Assets::WallRight));	// 右の壁

	Box::FromPoints(Vec3{ -16, 0, -16 }, Vec3{ 16, -2, 16 }).draw(TextureAsset(Assets::Wood));	// 机
}

void FieldScene::initLighting() const
{
	Graphics3D::SetSunColor(ColorF{ 1.0 });				// 平行光
	Graphics3D::SetSunDirection(Vec3{ 0.25, 0.75, -0.6 }.normalized());
}
