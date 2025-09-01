// Player class

# pragma once

# include "PlayerInput.hpp"
# include "../util/Util.hpp"

class PlayerCharacter
{
public:

	// コンストラクタ
	PlayerCharacter();

	// 更新処理
	virtual void update(const double deltaTime, const Vec3 cameraForward);

	// 描画処理
	virtual void draw() const;

	// プレイヤー座標の取得
	Vec3 GetPlayerPosition() const;

	// プレイヤーの向きの取得
	Quaternion GetPlayerRotation() const;

protected:

	// プレイヤーの位置
	Vec3 m_playerPosition;

	// プレイヤーの回転
	Quaternion m_playerRotation;

	// モデル
	const Model m_siv3dkun;
};
