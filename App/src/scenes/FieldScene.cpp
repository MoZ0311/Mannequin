// FieldScene class

# include "FieldScene.hpp"

using namespace Config::Scene;
using namespace Config::Scene::Field;
using namespace Config::Camera;

FieldScene::FieldScene(const InitData& init)
	: IScene{ init }
	, m_fieldArea{ FieldSize }
	, m_uiDrawer{}
	, m_renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes }
	, m_effect{}
	, m_player{ m_fieldArea }
	, m_camera{ m_renderTexture.size(), FOV::Narrow }
	, m_cameraController{ m_camera }
	, m_trashManager{ m_fieldArea, m_player }
{
	initLighting();
}

void FieldScene::update()
{
	// マウス位置を中央に固定
	Cursor::RequestStyle(CursorStyle::Hidden);
	Cursor::SetPos(Scene::Center());
	Cursor::RequestStyle(CursorStyle::Hidden);

	// シーンにおける前フレームからの経過時間
	const double deltaTime{ Scene::DeltaTime() };

	// プレイヤーの更新
	m_player.update(deltaTime, m_cameraController.getCameraForward(), m_trashManager.isCollidedPlayer());

	// カメラの更新
	m_cameraController.update(deltaTime, m_player.getPlayerPosition(), m_player.getPlayerRotation());

	// 直前の攻撃状態をキャッシュ
	const bool prevDamaged{ m_trashManager.isDamaged() };

	// 生成クラスの更新
	m_trashManager.update(deltaTime);

	// ゴミの個数で、クリア
	if (m_trashManager.getDeletedTrashCount() >= 10)
	{
		changeScene(State::Clear, ChangeDuration);
	}

	if (!prevDamaged && m_trashManager.isDamaged())
	{
		// ゴミが攻撃されていれば、攻撃判定の場所にエフェクト発生
		const Vec2& effectPostion{ Util::WorldToScreenPosition(m_player.getAttackCollider().center, m_camera) };
		m_effect.add<StarEffect>(effectPostion);
	}

	// UIの更新
	m_uiDrawer.update(m_trashManager.getDeletedTrashCount());

	// debug
	if (KeyQ.down())
	{
		AudioAsset(Assets::Explode).playOneShot();
		const Vec2& effectPostion{ Util::WorldToScreenPosition(m_player.getInsideCollider().center, m_camera) };
		m_effect.add<HexEffect>(effectPostion);
		changeScene(State::Field, ChangeDuration);
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

	// UI描画
	m_uiDrawer.draw();

	// エフェクト描画
	{
		const ScopedRenderStates2D blend{ BlendState::Additive };
		m_effect.update();
	}
}

void FieldScene::drawRoom() const
{
	Plane{ Vec3{ 0.0, RoomOffset - RoomSize / 2.0f, 0.0 }, RoomSize }.draw(TextureAsset(Assets::Floor));	// ゆか
	Plane{ Vec3{ 0.0, RoomOffset, RoomSize / 2.0f }, RoomSize }.draw(Quaternion::RotateX(-90_deg), TextureAsset(Assets::WallFront));	// 奥の壁
	Plane{ Vec3{ 0.0, RoomOffset, -RoomSize / 2.0f }, RoomSize }.draw(Quaternion::RotateX(-90_deg), TextureAsset(Assets::WallRear));	// 手前の壁
	Plane{ Vec3{ -RoomSize / 2.0f, RoomOffset, 0.0 }, RoomSize }.draw(Quaternion::RollPitchYaw(-90_deg, 90_deg, 0_deg), TextureAsset(Assets::WallLeft));	// 左の壁
	Plane{ Vec3{ RoomSize / 2.0f, RoomOffset, 0.0 }, RoomSize }.draw(Quaternion::RollPitchYaw(-90_deg, 90_deg, 0_deg), TextureAsset(Assets::WallRight));	// 右の壁

	Box::FromPoints(Vec3{ -16, 0, -16 }, Vec3{ 16, -2, 16 }).draw(TextureAsset(Assets::Wood));	// 机
}

void FieldScene::initLighting() const
{
	Graphics3D::SetSunColor(ColorF{ 1.0 });				// 平行光
	Graphics3D::SetSunDirection(LightDirection.normalized());
}
