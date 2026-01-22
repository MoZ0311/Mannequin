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
		ClearPrint();
		if (!app.run())
		{
			break;
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
