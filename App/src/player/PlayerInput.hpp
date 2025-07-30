#pragma once

struct PlayerInput
{
	// プレイヤーの移動方向の算出
	static Vec3 GetInputVector()
	{
		Vec3 inputVector{};

		// コントローラー接続確認
		auto& controller{ XInput(0) };

		if (controller.isConnected())
		{
			// 左スティックの値を使用
			inputVector = { controller.leftThumbX, inputVector.y, controller.leftThumbY };
		}
		else
		{
			// キー入力を二次元ベクトルに
			int32 upInput = KeyW.pressed() ? 1 : 0;
			int32 downInput = KeyS.pressed() ? 1 : 0;
			int32 leftInput = KeyA.pressed() ? 1 : 0;
			int32 rightInput = KeyD.pressed() ? 1 : 0;

			inputVector = { rightInput - leftInput, inputVector.y, upInput - downInput };
		}

		return inputVector.normalized();
	}

	static bool KeyMenu()
	{
		InputGroup menuKey = (KeyTab | XInput(0).buttonY);
		return menuKey.pressed();
	}
};
