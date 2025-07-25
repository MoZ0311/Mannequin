#pragma once

#include <Siv3D.hpp>

namespace Config
{
	inline constexpr Size ScreenSize{ 1280, 720 };
}

namespace SceneConfig
{
	enum class State
	{
		Title,
		Field,
		Battle,
		Over,
	};

	inline constexpr SecondsF ChangeDuration = 0.5s;
	using App = SceneManager<State>;

	namespace Field
	{
		inline constexpr ColorF BackgroundColor{ 0.4, 0.6, 0.8 };
	}
}

namespace Components
{
	inline constexpr Size ButtonSize{ 300, 60 };
	inline constexpr Transition ButtonTransition{ 0.4s, 0.2s };
	inline constexpr Point ButtonOffset{ 0, 100 };
	inline constexpr ColorF ButtonTextCollor{ 0.25 };
}
