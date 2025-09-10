# pragma once

# include <Siv3D.hpp>

namespace Config
{
	// 画面サイズ
	static inline constexpr Size ScreenSize{ 1280, 720 };

	// トリガーの閾値
	static inline constexpr float TriggerThreshold{ 0.3f };

	namespace Camera
	{
		// 視野角
		namespace FOV
		{
			static inline constexpr double Narrow{ 30_deg };
			static inline constexpr double Wide{ 60_deg };
		}

		// ピッチ
		namespace Pitch
		{
			static inline constexpr double Min{ 5_deg };
			static inline constexpr double Max{ 90_deg };

			static inline constexpr double Default{ 75_deg };
		}

		// 距離
		namespace Distance
		{
			static inline constexpr float Near{ 10.0f };
			static inline constexpr float Far{ 12.0f };
		}

		// 回転速度
		static inline constexpr float RotateSpeed{ 3.5f };

		// イース係数
		static inline constexpr float Interpolation{ 0.05f };

		// 初期値のずれを修正するためのオフセット
		static inline constexpr double RotateOffset{ 90_deg };
	}

	namespace Player
	{
		// 移動速度
		namespace MoveSpeed
		{
			static inline constexpr float DefaultSpeed{ 10.0f };
			static inline constexpr float DashSpeed{ 25.0f };
		}
		
		// 回転速度
		static inline constexpr float RotateSpeed{ 10.0f };

		// アニメーション再生速度
		static inline constexpr float AnimationSpeed{ 8.0f };
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
		static inline constexpr SecondsF ChangeDuration{ 0.5s };
		using SceneApp = SceneManager<State, GameData>;

		namespace Field
		{
			// 背景色
			static inline constexpr ColorF BackgroundColor{ 0.4, 0.6, 0.8 };
		}
	}
}

namespace Assets
{
	static inline const String UV{ U"UV" };
	static inline const String Title{ U"Title" };
	static inline const String Over{ U"Over" };
	static inline const String Makinas{ U"Makinas" };

	// アセット登録
	static inline void Register()
	{
		// テクスチャのアセット化
		TextureAsset::Register(UV, U"example/texture/uv.png", TextureDesc::MippedSRGB);
		TextureAsset::Register(Title, U"assets/background/title.png", TextureDesc::MippedSRGB);
		TextureAsset::Register(Over, U"assets/background/over.png", TextureDesc::MippedSRGB);

		// フォントのアセット化
		FontAsset::Register(Makinas, FontMethod::MSDF, 48, U"assets/fonts/Makinas-4-Square.otf");

		// 絵文字の追加
		static const Font Emoji{ FontMethod::MSDF, 48, Typeface::ColorEmoji };
		FontAsset(Makinas).addFallback(Emoji);
	}

	namespace Models
	{
		// コライダーの大きさ
		static inline Vec3 MannequinColliderScale{ 1.0, 1.0, 1.5 };
	}
}

namespace Components
{
	// ボタンのサイズ
	static inline constexpr Size ButtonSize{ 300, 60 };

	// ボタンの枠の太さ
	static inline constexpr float ButtonThickness{ 2.0f };

	// ボタンの丸み
	static inline constexpr float ButtonRoundness{ ButtonSize.y / 2.0f };

	// ボタンのトランジション
	static inline constexpr Transition ButtonTransition{ 0.4s, 0.2s };

	// ボタン同士の間隔
	static inline constexpr Point ButtonOffset{ 0, 100 };

	// ボタンの文字の色
	static inline constexpr ColorF ButtonTextCollor{ 0.3 };

	// タイトル画面でのボタンの位置
	static inline constexpr Point TitleButtonPoint{ 980, 500 };

	// ゲームオーバー画面でのボタンの位置
	static inline constexpr Point OverButtonPoint{ 640, 520 };
}

namespace UI
{
	static inline constexpr Point StatusWindowPoint{ 0, 200 };
	static inline constexpr Size StatusWindowSize{ 400, StatusWindowPoint.y };
	static inline constexpr float WindowRoundness{ StatusWindowSize.y / 1.5f };
}
