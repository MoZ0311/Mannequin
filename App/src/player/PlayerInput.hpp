#pragma once

# include "../core/Config.hpp"

struct PlayerInput
{
	// プレイヤーの移動方向の算出
	static Vec2 GetInputAxis()
	{
		Vec2 inputVector{};

		// コントローラー接続確認
		auto& controller{ XInput(0) };

		if (controller.isConnected())
		{
			// 左スティックの値を使用
			inputVector = { controller.leftThumbX, controller.leftThumbY };
		}
		else
		{
			// キー入力を二次元ベクトルに
			int32 forwardInput = KeyW.pressed() ? 1 : 0;
			int32 backwardInput = KeyS.pressed() ? 1 : 0;
			int32 leftInput = KeyA.pressed() ? 1 : 0;
			int32 rightInput = KeyD.pressed() ? 1 : 0;

			inputVector = { rightInput - leftInput, forwardInput - backwardInput };
		}

		return inputVector.normalized();
	}

	static bool KeyMenu()
	{
		InputGroup menuKey{ KeyTab | XInput(0).buttonY };
		return menuKey.pressed();
	}
};
