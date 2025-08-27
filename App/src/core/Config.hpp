# pragma once

# include <Siv3D.hpp>
# include <memory>

namespace Config
{
	// 画面サイズ
	inline constexpr Size ScreenSize{ 1280, 720 };

	// トリガーの閾値
	inline constexpr double TriggerThreshold{ 0.3 };

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
			inline constexpr double Near{ 10.0 };
			inline constexpr double Far{ 12 };
		}

		// 回転速度
		inline constexpr double RotateSpeed{ 2.0 };

		// 初期値のずれを修正するためのオフセット
		inline constexpr double RotateOffset{ 90_deg };

		// イース係数
		inline constexpr double Interpolation{ 0.05 };
	}

	namespace Player
	{
		// 移動速度
		inline constexpr double MoveSpeed{ 10.0 };

		// 回転速度
		inline constexpr double RotateSpeed{ 10.0 };
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
	// アセット登録
	inline void Register()
	{
		TextureAsset::Register(U"UV", U"example/texture/uv.png", TextureDesc::MippedSRGB);
	}

	inline const String UV{ U"UV" };
}

namespace Components
{
	// ボタンのサイズ
	inline constexpr Size ButtonSize{ 300, 60 };

	// ボタンのトランジション
	inline constexpr Transition ButtonTransition{ 0.4s, 0.2s };

	// ボタン同士の間隔
	inline constexpr Point ButtonOffset{ 0, 100 };

	// ボタンの文字の色
	inline constexpr ColorF ButtonTextCollor{ 0.25 };
}
