# pragma once

# include "../core/Config.hpp"

struct PlayerInput
{
	static inline constexpr uint8 PlayerIndex{ 0 };

	// プレイヤーの移動方向の算出
	static inline Vec2 GetMovementAxis()
	{
		// コントローラー入力を取得
		detail::XInput_impl controller{ XInput(PlayerIndex) };
		if (controller.isConnected())
		{
			// デッドゾーン設定
			controller.setLeftThumbDeadZone();

			// 左スティックの入力値を使用
			const Vec2 inputVector{ controller.leftThumbX, controller.leftThumbY };

			// 値が0でなければ、return
			if (!inputVector.isZero())
			{
				return inputVector;
			}
		}
		
		// キー入力を平面ベクトルに変換(trueを1, falseを0として算術演算)
		const Vec2 keyInputVector{ KeyD.pressed() - KeyA.pressed(), KeyW.pressed() - KeyS.pressed() };
		return keyInputVector.normalized();
	}

	// カメラの操作
	static inline Vec2 GetCameraAxis()
	{
		// コントローラー入力を取得
		detail::XInput_impl controller{ XInput(PlayerIndex) };
		if (controller.isConnected())
		{
			// デッドゾーン設定
			controller.setRightThumbDeadZone();

			// 右スティックの入力値を使用
			const Vec2 inputVector{ -controller.rightThumbX, controller.rightThumbY };

			// 値が0でなければ、return
			if (!inputVector.isZero())
			{
				return inputVector * Config::Camera::RotateSpeed;
			}
		}

		// カーソルの移動量を取得
		return Cursor::DeltaF();
	}

	static inline bool KeyConfirm()
	{
		static const InputGroup confirmKey{ KeySpace | KeyEnter | MouseL | XInput(PlayerIndex).buttonB };
		return confirmKey.down();
	}

	static inline bool KeyCancel()
	{
		static const InputGroup cancelKey{ KeyBackspace | KeyC | MouseR | XInput(PlayerIndex).buttonA };
		return cancelKey.down();
	}

	static inline bool KeyDash()
	{
		const bool pressedDashKey{ KeyShift.pressed() || XInput(PlayerIndex).rightTrigger > Config::TriggerThreshold };
		return pressedDashKey;
	}

	static inline bool KeyMenu()
	{
		static const InputGroup menuKey{ KeyTab | XInput(PlayerIndex).buttonY };
		return menuKey.down();
	}

	static inline bool StopMove()
	{
		static const InputGroup stopKey{ KeyF | MouseM | XInput(0).buttonRB };
		return stopKey.pressed();
	}

	static inline bool ResetCamera()
	{
		static const InputGroup resetKey{ MouseM | XInput(PlayerIndex).buttonA | XInput(PlayerIndex).buttonRThumb };
		return resetKey.down();
	}

	static inline bool KeyLiteAttack()
	{
		static const InputGroup liteAttackKey{ MouseL | XInput(PlayerIndex).buttonX };
		return liteAttackKey.down();
	}

	static inline bool KeyGuard()
	{
		const bool guardKey{ KeyR.pressed() || XInput(PlayerIndex).leftTrigger > Config::TriggerThreshold };
		return guardKey;
	}
};
