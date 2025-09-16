# pragma once

struct BubbleEffect : IEffect
{
	struct Bubble
	{
		Vec2 offset;
		double startTime;
		double scale;
		double rotate;
	};

	Vec2 m_pos;

	Array<Bubble> m_bubbles;

	inline BubbleEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		for (uint8 i{ 0 }; i < 8; ++i)
		{
			Bubble bubble{
				.offset = RandomVec2(Circle{ 50 }),
				.startTime = Random(-0.3, 0.1),
				.scale = Random(0.5, 0.7),
				.rotate = Random(0_deg, 180_deg)
			};
			m_bubbles << bubble;
		}
	}

	inline bool update(double t) override
	{
		for (const auto& bubble : m_bubbles)
		{
			const double t2 = (bubble.startTime + t);

			if (not InRange(t, 0.0, 1.0))
			{
				continue;
			}

			const double e = EaseOutExpo(t2);

			Shape2D::Star((e * 40 * bubble.scale), (m_pos + bubble.offset + (bubble.offset * 4 * t)), bubble.rotate)
				.draw(ColorF{ Palette::Orangered, 0.15 })
				.drawFrame((30.0 * (1.0 - e) * bubble.scale), ColorF{ Palette::Orangered });
		}

		return (t < 0.4);
	}
};
