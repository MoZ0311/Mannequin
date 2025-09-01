#pragma once

# include "../core/Config.hpp"

struct PlayerInput
{
	static inline constexpr uint8 PlayerIndex{ 0 };

	// プレイヤーの移動方向の算出
	static Vec2 GetMovementAxis()
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
	static Vec2 GetCameraAxis()
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

	static bool KeyDash()
	{
		const bool pressedDashKey{ KeyShift.pressed() || XInput(PlayerIndex).rightTrigger > Config::TriggerThreshold };
		return pressedDashKey;
	}

	static bool KeyMenu()
	{
		const InputGroup menuKey{ KeyTab | XInput(PlayerIndex).buttonY };
		return menuKey.down();
	}

	static bool ResetCamera()
	{
		const InputGroup resetKey{ KeyR | XInput(PlayerIndex).buttonA | XInput(PlayerIndex).buttonRThumb };
		return resetKey.down();
	}
};
