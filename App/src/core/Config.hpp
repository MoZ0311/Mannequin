# pragma once

# include <Siv3D.hpp>
// # include <memory>

namespace Config
{
	// 画面サイズ
	inline constexpr Size ScreenSize{ 1280, 720 };

	// トリガーの閾値
	inline constexpr float TriggerThreshold{ 0.3f };

	namespace Camera
	{
		// 視野角
		namespace FOV
		{
			inline constexpr double Narrow{ 30_deg };
			inline constexpr double Wide{ 60_deg };
		}

		// ピッチ
		namespace Pitch
		{
			inline constexpr double Min{ 5_deg };
			inline constexpr double Max{ 90_deg };

			inline constexpr double Default{ 75_deg };
		}

		// 距離
		namespace Distance
		{
			inline constexpr float Near{ 10.0f };
			inline constexpr float Far{ 12.0f };
		}

		// 回転速度
		inline constexpr float RotateSpeed{ 2.0f };

		// イース係数
		inline constexpr float Interpolation{ 0.05f };

		// 初期値のずれを修正するためのオフセット
		inline constexpr double RotateOffset{ 90_deg };
	}

	namespace Player
	{
		// 移動速度
		namespace MoveSpeed
		{
			inline constexpr float DefaultSpeed{ 10.0f };
			inline constexpr float DashSpeed{ 25.0f };
		}
		
		// 回転速度
		inline constexpr float RotateSpeed{ 10.0f };
	}

	namespace Scene
	{
		enum class State
		{
			Title,
			Field,
			Battle,
			Over,
		};

		struct GameData
		{
			// 直前のワールド座標
			Vec3 prevWorldPosition;
		};

		// シーン遷移の間隔
		inline constexpr SecondsF ChangeDuration{ 0.5s };
		using SceneApp = SceneManager<State, GameData>;

		namespace Field
		{
			// 背景色
			inline constexpr ColorF BackgroundColor{ 0.4, 0.6, 0.8 };
		}
	}
}

namespace Assets
{
	inline const String UV{ U"UV" };
	inline const String Title{ U"Title" };
	inline const String Over{ U"Over" };
	inline const String Makinas{ U"Makinas" };

	// アセット登録
	inline void Register()
	{
		// テクスチャのアセット化
		TextureAsset::Register(UV, U"example/texture/uv.png", TextureDesc::MippedSRGB);
		TextureAsset::Register(Title, U"assets/background/title.png", TextureDesc::MippedSRGB);
		TextureAsset::Register(Over, U"assets/background/over.png", TextureDesc::MippedSRGB);

		// フォントのアセット化
		FontAsset::Register(Makinas, FontMethod::MSDF, 48, U"fonts/Makinas-4-Square.otf");

		// 絵文字の追加
		const Font Emoji{ FontMethod::MSDF, 48, Typeface::ColorEmoji };
		FontAsset(Makinas).addFallback(Emoji);
	}
}

namespace Components
{
	// ボタンのサイズ
	inline constexpr Size ButtonSize{ 300, 60 };

	inline constexpr float ButtonThickness{ 2.0f };

	// ボタンの丸み
	inline constexpr float ButtonRoundness{ ButtonSize.y / 2.0f };

	// ボタンのトランジション
	inline constexpr Transition ButtonTransition{ 0.4s, 0.2s };

	// ボタン同士の間隔
	inline constexpr Point ButtonOffset{ 0, 100 };

	// ボタンの文字の色
	inline constexpr ColorF ButtonTextCollor{ 0.3 };

	// タイトル画面でのボタンの位置
	inline constexpr Point TitleButtonPoint{ 980, 500 };

	// ゲームオーバー画面でのボタンの位置
	inline constexpr Point OverButtonPoint{ 640, 520 };
}
