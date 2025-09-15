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
			static inline constexpr float Near{ 7.5f };
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
			static inline constexpr float Default{ 10.0f };
			static inline constexpr float Sprint{ 25.0f };
		}
		
		// 回転速度
		static inline constexpr float RotateSpeed{ 10.0f };

		// アニメーション再生速度
		namespace AnimationSpeed
		{
			static inline constexpr float Default{ 8.0f };
			static inline constexpr float Attack{ 11.0f };
		}

		// 入力バッファの制限
		static inline constexpr uint8 MaxBufferSize{ 1 };
	}

	namespace Scene
	{
		enum class State
		{
			Title,
			Field,
			Over,
		};

		// シーン遷移の間隔
		static inline constexpr SecondsF ChangeDuration{ 0.5s };
		using SceneApp = SceneManager<State>;

		namespace Field
		{
			// 背景色
			static inline constexpr ColorF BackgroundColor{ 0.4, 0.6, 0.8 };

			// 光の向き
			static inline constexpr Vec3 LightDirection{ 0.25, 0.75, -0.6 };

			// フィールドの広さ
			static inline constexpr uint8 FieldSize{ 32 };

			// 部屋全体の広さ
			static inline constexpr uint8 RoomSize{ 64 };

			// 部屋のオフセット
			static inline constexpr float RoomOffset{ 16.0f };
		}
	}
}

namespace Assets
{
	static inline const String Title{ U"Title" };
	static inline const String Over{ U"Over" };
	static inline const String Wood{ U"Wood" };
	static inline const String Floor{ U"Floor" };
	static inline const String WallFront{ U"WallFront" };
	static inline const String WallRear{ U"WallRear" };
	static inline const String WallLeft{ U"WallLeft" };
	static inline const String WallRight{ U"WallRight" };

	static inline const String BGM{ U"BGM" };
	static inline const String Blocking{ U"Blocking" };
	static inline const String BlowLite{ U"BlowLite" };
	static inline const String BlowHeavy{ U"BlowHeavy" };
	static inline const String Damage{ U"Damage" };
	static inline const String Guard{ U"Guard" };

	static inline const String Makinas{ U"Makinas" };

	// アセット登録
	static inline void Register()
	{
		// テクスチャのアセット化
		TextureAsset::Register(Title, U"assets/background/title.png", TextureDesc::MippedSRGB);
		TextureAsset::Register(Over, U"assets/background/over.png", TextureDesc::MippedSRGB);
		TextureAsset::Register(Wood, U"assets/background/wood.jpg", TextureDesc::MippedSRGB);
		TextureAsset::Register(Floor, U"assets/background/floor.jpg", TextureDesc::MippedSRGB);
		TextureAsset::Register(WallFront, U"assets/background/wall_front.jpg", TextureDesc::MippedSRGB);
		TextureAsset::Register(WallRear, U"assets/background/wall_rear.jpg", TextureDesc::MippedSRGB);
		TextureAsset::Register(WallLeft, U"assets/background/wall_left.jpg", TextureDesc::MippedSRGB);
		TextureAsset::Register(WallRight, U"assets/background/wall_right.jpg", TextureDesc::MippedSRGB);

		// オーディオのアセット化
		AudioAsset::Register(BGM, Audio::Stream, U"assets/audios/bgm.mp3", Loop::Yes);
		AudioAsset::Register(Blocking, U"assets/audios/blocking.mp3");
		AudioAsset::Register(BlowLite, U"assets/audios/blow_lite.mp3");
		AudioAsset::Register(BlowHeavy, U"assets/audios/blow_heavy.mp3");
		AudioAsset::Register(Damage, U"assets/audios/damage.mp3");
		AudioAsset::Register(Guard, U"assets/audios/guard.mp3");

		// フォントのアセット化
		FontAsset::Register(Makinas, FontMethod::MSDF, 48, U"assets/fonts/Makinas-4-Square.otf");

		// 絵文字の追加
		static const Font Emoji{ FontMethod::MSDF, 48, Typeface::ColorEmoji };
		FontAsset(Makinas).addFallback(Emoji);
	}

	namespace Models
	{
		// コライダーの大きさ
		static inline constexpr Vec3 MannequinInsideColliderScale{ 0.7, 0.9, 1.5 };
		static inline constexpr Vec3 MannequinOutsideColliderScale{ 1.0, 1.0, 3.5 };
		static inline constexpr Vec3 MannequinAttackColliderScale{ 2.0, 0.5, 4.0 };
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
