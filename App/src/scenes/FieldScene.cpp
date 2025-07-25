// FieldScene class

#include "FieldScene.hpp"

FieldScene::FieldScene(const InitData& init)
	: IScene{ init }
	, renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes }
	, cam{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } }
{
	initLighting();
}

void FieldScene::update()
{
	cam.update(2.0);
}

void FieldScene::draw() const
{
	Graphics3D::SetCameraTransform(cam);

	// 3D描画
	{
		const ScopedRenderTarget3D target{ renderTexture.clear(SceneConfig::Field::BackgroundColor.removeSRGBCurve()) };

		Plane{ 64 }.draw(TextureAsset(U"UV"));
		Box{ -8, 2, 0, 4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
	}

	// 2Dに転送
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}
}

void FieldScene::initLighting() const
{
	Graphics3D::SetGlobalAmbientColor(ColorF{ 0.1 });	// 環境光
	Graphics3D::SetSunColor(ColorF{ 1.0 });				// 平行光
	Graphics3D::SetSunDirection(Vec3{ 0.3, 1.0, 0.2 }.normalized());
}
