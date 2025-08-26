#pragma once

struct Util
{
	// クオータニオンからオイラー角への変換
	static Vec3 QuaternionToEuler(const Quaternion& q)
	{
		const float x{ q.getX() };
		const float y{ q.getY() };
		const float z{ q.getZ() };
		const float w{ q.getW() };

		// const Vec3 eular{ q.() };

		// X軸周りの回転 (ロール)
		const double roll{ Atan2(2.0 * (w * x + y * z), 1.0 - 2.0 * (x * x + y * y)) };

		// Y軸周りの回転 (ピッチ)
		double pitch{};
		const double pitch_input{ 2.0 * (w * y - z * x) };

		// ジンバルロックのチェック
		if (Abs(pitch_input) >= 1.0)
		{
			// 90度または-90度のとき
			// 特異点のため、ロールは0とし、ヨーを計算する
			// return Vec3(0.0, Math::TwoPi * pitch_input, 2.0 * Atan2(x, w));

			pitch = copysign(Math::Pi / 2, pitch_input);
		}
		else
		{
			pitch = Asin(pitch_input);
		}

		// Z軸周りの回転 (ヨー)
		const double yaw = Atan2(2.0 * (w * z + x * y), 1.0 - 2.0 * (y * y + z * z));

		return Vec3(roll, pitch, yaw);
	}
};
