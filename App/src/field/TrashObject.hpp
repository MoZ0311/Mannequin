// TrashObject class

# pragma once

# include "../player/PlayerCharacter.hpp"
# include "../core/ModelAssets.hpp"
# include "../util/EEfectDrawer.hpp"

class TrashObject
{
public:

	// コンストラクタ
	TrashObject(const Vec3& position, const Model& model, const PlayerCharacter& instance);

	// 更新処理
	void update(const double deltaTime);

	// 描画処理
	void draw() const;

	// プレイヤーに接触したか
	const bool isCollidedPlayer() const;

	// 攻撃を受けたか
	const bool isDamaged(const Model& model) const;

	// 地面についたか
	const bool isGrounded() const;

private:

	// プレイヤーのインスタンス
	const PlayerCharacter& m_playerInstance;

	// モデル
	const Model& m_model;

	// エフェクト
	Effect m_effect;

	// 現在速度
	Vec3 m_velocity;

	// 現在位置
	Vec3 m_position;

	// 現在の回転
	const double m_rotation;
};
