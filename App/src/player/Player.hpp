// Player class

# pragma once

# include "PlayerInput.hpp"

class Player
{
public:

	// インスタンスの作成 / 取得
	static Player& GetInstance();

	// 更新処理
	void update(const double deltaTime, const Vec3 forwardVector);

	// 描画処理
	void draw() const;

	// プレイヤー座標の取得
	Vec3 GetPlayerPosition() const;

private:

	// コンストラクタ
	Player();

	// シングルトン
	static std::unique_ptr<Player> instance;

	// 移動速度
	double m_moveSpeed;

	Sphere m_sphere;
};
