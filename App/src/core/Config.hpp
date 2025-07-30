# pragma once

# include <Siv3D.hpp>

namespace Config
{
	inline constexpr Size ScreenSize{ 1280, 720 };

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

		inline constexpr SecondsF ChangeDuration = 0.5s;
		using App = SceneManager<State, GameData>;

		namespace Field
		{
			inline constexpr ColorF BackgroundColor{ 0.4, 0.6, 0.8 };
		}
	}
}

namespace Assets
{
	inline void Register()
	{
		TextureAsset::Register(U"UV", U"example/texture/uv.png", TextureDesc::MippedSRGB);
	}

	inline const String UV = U"UV";
}

namespace Components
{
	inline constexpr Size ButtonSize{ 300, 60 };
	inline constexpr Transition ButtonTransition{ 0.4s, 0.2s };
	inline constexpr Point ButtonOffset{ 0, 100 };
	inline constexpr ColorF ButtonTextCollor{ 0.25 };
}
