# pragma once

struct BubbleEffect : IEffect
{
	struct Bubble
	{
		Vec2 offset;
		double scale;
	};

	Vec2 m_pos;

	Array<Bubble> m_bubbles;

	inline BubbleEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		for (uint8 i{ 0 }; i < 4; ++i)
		{
			Bubble bubble{
				.offset = RandomVec2(Circle{10}),
				.scale = Random(0.5, 0.7),
			};
			m_bubbles << bubble;
		}
	}

	inline bool update(double t) override
	{
		for (const auto& bubble : m_bubbles)
		{
			if (not InRange(t, 0.0, 1.0))
			{
				continue;
			}

			const double e = EaseOutExpo(t);

			Circle{ (m_pos + bubble.offset + (bubble.offset * 4 * t)), (e * 40 * bubble.scale) }
				.draw(ColorF{ Palette::Orange, 0.15f })
				.drawFrame((30.0 * (1.0 - e) * bubble.scale), ColorF{ Palette::Orangered, 0.3f });
		}

		return (t < 0.3);
	}
};
