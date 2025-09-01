#pragma once

class Util
{
public:

	// クオータニオンからオイラー角への変換
	static Vec3 QuaternionToEuler(const Quaternion& q)
	{
		const float x{ q.getX() };
		const float y{ q.getY() };
		const float z{ q.getZ() };
		const float w{ q.getW() };

		// X軸周りの回転 (ロール)
		const double roll{ Atan2(2.0 * (w * x + y * z), 1.0 - 2.0 * (x * x + y * y)) };

		// Y軸周りの回転 (ピッチ)
		double pitch{};
		const double pitch_input{ 2.0 * (w * y - z * x) };

		// ジンバルロックのチェック
		if (Abs(pitch_input) >= 1.0)
		{
			pitch = copysign(Math::Pi / 2, pitch_input);
		}
		else
		{
			pitch = Asin(pitch_input);
		}

		// Z軸周りの回転 (ヨー)
		const double yaw{ Atan2(2.0 * (w * z + x * y), 1.0 - 2.0 * (y * y + z * z)) };

		return Vec3(roll, pitch, yaw);
	}
	
	static void DrawDiscFrame(const Vec3& centor, const double radius)
	{
		// ユニットの情報をもとに、円周上の点群を作成
		const Array<Vec2> points{ Util::MakeCirclePoints(centor, radius + 0.0001f) };

		// 生成した点を線で結んで描画
		for (int8 i{ 0 }; i < points.size(); ++i)
		{
			const Vec3& p1{ points[i].x, 0, points[i].y };
			const Vec3& p2{ points[(i + 1) % points.size()].x, 0, points[(i + 1) % points.size()].y };
			Line3D{ p1, p2 }.draw(Palette::White);
		}
	}

private:

	// 設定された位置と半径をもとに、円周上の点を生成する
	static Array<Vec2> MakeCirclePoints(const Vec3& center, const double radius)
	{
		const uint8 segments{ 60 };

		// 円周上の点はsegment個
		Array<Vec2> points{ segments };

		for (int8 i{ 0 }; i < segments; ++i)
		{
			const double angle{ i * (Math::TwoPi / segments) };
			const Vec2 point{ center.xz() + Vec2{ radius * std::cos(angle), radius * std::sin(angle) } };
			points[i] = point;
		}
		return points;
	}
};
