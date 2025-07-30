// FieldScene class

# include "FieldScene.hpp"

FieldScene::FieldScene(const InitData& init)
	: IScene{ init }
	, m_renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes }
	, m_camera{ m_renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } }
{
	initLighting();

	// シングルトン生成
	Player::Init();
}

FieldScene::~FieldScene()
{
	// シングルトン破棄
	Player::Release();
}

void FieldScene::update()
{
	double deltaTime = Scene::DeltaTime();
	m_camera.setView(m_camera.getEyePosition(), Player::GetInstance()->GetPlayerPosition());
	Player::GetInstance()->update(deltaTime);

	if (PlayerInput::KeyMenu())
	{
		Print << U"Menu";
	}
}

void FieldScene::draw() const
{
	Graphics3D::SetCameraTransform(m_camera);

	// 3D描画
	{
		const ScopedRenderTarget3D target{ m_renderTexture.clear(Field::BackgroundColor.removeSRGBCurve()) };

		Plane{ 64 }.draw(TextureAsset(Assets::UV));
		Box{ -8, 2, 0, 4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());

		Player::GetInstance()->draw();
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
