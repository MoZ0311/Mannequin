#pragma once

# include "../core/Config.hpp"

struct PlayerInput
{
	// プレイヤーの移動方向の算出
	static Vec2 GetMovementAxis()
	{
		// 入力された平面ベクトル
		Vec2 inputVector{};

		// コントローラー入力を取得
		detail::XInput_impl controller{ XInput(0) };
		if (controller.isConnected())
		{
			// デッドゾーン設定
			controller.setLeftThumbDeadZone();

			// 左スティックの入力値を使用
			inputVector = { controller.leftThumbX, controller.leftThumbY };

			// 値が0でなければ、return
			if (!inputVector.isZero())
			{
				return inputVector;
			}
		}
		
		// キー入力を平面ベクトルに変換(trueを1, falseを0として算術演算)
		inputVector = Vec2{ KeyD.pressed() - KeyA.pressed(), KeyW.pressed() - KeyS.pressed() }.normalize();
		return inputVector;
	}

	// カメラの操作
	static Vec2 GetCameraAxis()
	{
		// コントローラー入力を取得
		detail::XInput_impl controller{ XInput(0) };
		if (controller.isConnected())
		{
			// デッドゾーン設定
			controller.setRightThumbDeadZone();

			// 右スティックの入力値を使用
			const Vec2 inputVector{ controller.rightThumbX, controller.rightThumbY };

			// 値が0でなければ、return
			if (!inputVector.isZero())
			{
				return inputVector;
			}
		}

		// カーソルの移動量を取得
		return Cursor::DeltaF();

	}

	static bool KeyMenu()
	{
		InputGroup menuKey{ KeyTab | XInput(0).buttonY };
		return menuKey.pressed();
	}
};
