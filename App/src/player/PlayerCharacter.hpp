// PlayerCharacter class

# pragma once

# include "PlayerInput.hpp"
# include "../util/Util.hpp"

class PlayerCharacter
{
public:

	// コンストラクタ
	PlayerCharacter();

	// 更新処理
	virtual void update(const double deltaTime, const Vec3& cameraForward);

	// 描画処理
	void draw() const;

	// プレイヤー座標の取得
	Vec3 getPlayerPosition() const;

	// プレイヤーの向きの取得
	Quaternion getPlayerRotation() const;

protected:

	// 移動処理
	void move(const double deltaTime, const Vec3& cameraForward);

	// アニメーション更新処理
	void animationUpdate();

	// プレイヤーの位置
	Vec3 m_playerPosition;

	// プレイヤーの回転
	Quaternion m_playerRotation;

	// アニメーション配列
	Array<Model> m_animationArray;

	// 攻撃アニメーションのバッファ
	std::queue<Array<Model>> m_attackInputBuffer;

	// アニメーション制御用のタイマー
	double m_animationTimer;

	// 攻撃中であるか
	bool m_isAttacking;
};
