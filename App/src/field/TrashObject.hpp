// TrashObject class

# pragma once

# include "../player/PlayerCharacter.hpp"
# include "../core/ModelAssets.hpp"

class TrashObject
{
public:

	// コンストラクタ
	TrashObject(const Vec3& position, const Model& model, const PlayerCharacter& instance, const Box& fieldArea);

	// 更新処理
	void update(const double deltaTime);

	// 描画処理
	void draw() const;

	// プレイヤーに接触したか
	const bool isCollidedPlayer() const;

	// 攻撃を受けたか
	const bool getIsDamaged() const;

	// 場外に出たか
	const bool isOutside() const;

	// 地面についたか
	const bool isGrounded() const;

private:

	// 攻撃を受けたか
	const bool isDamaged(const Model& model) const;

	// モデル
	const Model& m_model;

	// プレイヤーのインスタンス
	const PlayerCharacter& m_playerInstance;

	// 場内判定
	const Box& m_fieldArea;

	// エフェクト
	Effect m_effect;

	// 現在速度
	Vec3 m_velocity;

	// 現在位置
	Vec3 m_position;

	// 回転
	const double m_rotation;

	// 直前に被弾したか
	bool m_prevDamaged;

	// 現在被弾しているか
	bool m_isDamaged;

	// 直前に場外になったか
	bool m_prevOutside;
};
