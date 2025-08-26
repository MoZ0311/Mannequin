// Player class

# pragma once

# include "PlayerInput.hpp"

class Player
{
public:

	// コンストラクタ
	Player();

	// 更新処理
	void update(const double deltaTime, const Vec3 cameraForward);

	// 描画処理
	void draw() const;

	// プレイヤー座標の取得
	Vec3 GetPlayerPosition() const;

	// プレイヤーの向きの取得
	Quaternion GetPlayerRotation() const;

protected:

	// プレイヤーの位置
	Vec3 m_playerPosition;

	// プレイヤーの回転
	Quaternion m_playerRotation;

	// プレイヤーの攻撃範囲
	Circle m_attackRing;

	// モデル
	const Model m_siv3dkun;
};
