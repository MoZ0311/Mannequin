# include "App/src/core/Application.hpp"
# include "App/src/core/ModelAssets.hpp"

void Main()
{
	Assets::Register();
	ModelAssets::GetInstance();
	Application app{};

	// BGMを再生する
	AudioAsset(Assets::BGM).setVolume(0.25).play();

	while (System::Update())
	{
		if (!app.run())
		{
			break;
		}
	}
}
