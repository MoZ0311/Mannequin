// Player class

# pragma once

# include "PlayerInput.hpp"

class Player
{
public:

	// インスタンスの作成
	static void Init();

	// インスタンスの解放
	static void Release();

	// 更新処理
	void update(double& deltaTime);

	// 描画処理
	void draw() const;

	static Player* GetInstance();
	Vec3 GetPlayerPosition() const;

private:

	// コンストラクタ
	Player();

	// デストラクタ
	~Player();

	static Player* instance;

	// 移動速度
	double m_moveSpeed;

	Sphere m_sphere;
};
