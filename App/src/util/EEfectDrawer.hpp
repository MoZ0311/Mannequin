# pragma once

struct StarEffect : IEffect
{
	struct Star
	{
		Vec2 offset;
		double startTime;
		double scale;
		double rotate;
	};

	Vec2 m_pos;

	Array<Star> m_stars;

	inline StarEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		for (uint8 i{ 0 }; i < 8; ++i)
		{
			Star star{
				.offset = RandomVec2(Circle{ 50 }),
				.startTime = Random(-0.3, 0.1),
				.scale = Random(0.5, 0.7),
				.rotate = Random(0_deg, 180_deg)
			};
			m_stars << star;
		}
	}

	inline bool update(double t) override
	{
		for (const auto& star : m_stars)
		{
			const double t2 = (star.startTime + t);

			if (!InRange(t, 0.0, 1.0))
			{
				continue;
			}

			const double e = EaseOutExpo(t2);

			Shape2D::Star((e * 40 * star.scale), (m_pos + star.offset + (star.offset * 4 * t)), star.rotate)
				.draw(ColorF{ Palette::Orangered, 0.15 })
				.drawFrame((30.0 * (1.0 - e) * star.scale), ColorF{ Palette::Orangered });
		}

		return (t < 0.4);
	}
};

struct HexEffect : IEffect
{
	struct Hex
	{
		Vec2 offset;
		double startTime;
		double scale;
	};

	Vec2 m_pos;

	Array<Hex> m_hexes;

	inline HexEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		for (uint8 i{ 0 }; i < 32; ++i)
		{
			Hex hex{
				.offset = RandomVec2(Circle{ 100 }),
				.startTime = Random(-0.3, 0.1),
				.scale = Random(0.7, 1.5),
			};
			m_hexes << hex;
		}
	}

	inline bool update(double t) override
	{
		for (const auto& hex : m_hexes)
		{
			const double t2 = (hex.startTime + t);

			if (!InRange(t, 0.0, 1.0))
			{
				continue;
			}

			const double e = EaseOutExpo(t2);

			Shape2D::Hexagon((e * 40 * hex.scale), (m_pos + hex.offset + (hex.offset * 4 * t)), 30_deg)
				.draw(ColorF{ Palette::Mediumvioletred, 0.15 })
				.drawFrame((30.0 * (1.0 - e) * hex.scale), ColorF{ Palette::Crimson });
		}

		return (t < 0.4);
	}
};
