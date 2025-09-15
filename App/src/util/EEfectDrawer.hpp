# pragma once

struct BubbleEffect : IEffect
{
	struct Bubble
	{
		Vec2 offset;
		double startTime;
		double scale;
	};

	Vec2 m_pos;

	Array<Bubble> m_bubbles;

	BubbleEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		for (uint8 i{ 0 }; i < 10; ++i)
		{
			Bubble bubble{
				.offset = RandomVec2(Circle{5}),
				.startTime = Random(-0.3, 0.1), // 登場の時間差
				.scale = Random(0.1, 0.5),
			};
			m_bubbles << bubble;
		}
	}

	bool update(double t) override
	{
		for (const auto& bubble : m_bubbles)
		{
			const double t2 = (bubble.startTime + t);

			if (not InRange(t2, 0.0, 1.0))
			{
				continue;
			}

			const double e = EaseOutExpo(t2);

			Circle{ (m_pos + bubble.offset + (bubble.offset * 4 * t)), (e * 40 * bubble.scale) }
				.draw(ColorF{ Palette::Orangered, 0.15f })
				.drawFrame((30.0 * (1.0 - e) * bubble.scale), ColorF{ Palette::Orangered, 0.5f });
		}

		return (t < 0.3);
	}
};
