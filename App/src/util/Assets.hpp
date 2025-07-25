#pragma once

#include <Siv3D.hpp>

namespace Assets
{
	inline void Register()
	{
		TextureAsset::Register(U"UV", U"example/texture/uv.png", TextureDesc::MippedSRGB);
	}
}
