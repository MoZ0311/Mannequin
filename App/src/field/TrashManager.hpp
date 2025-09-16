// TrashGenerator class

# pragma once

# include <memory>
# include "TrashObject.hpp"
# include "../core/ModelAssets.hpp"

class TrashManager
{
public:

	// コンストラクタ
	TrashManager(const Box& fieldArea, const PlayerCharacter& instance);

	// 更新処理
	void update(const double deltaTime);

	// 描画処理
	void draw() const;

	// 接触したか
	const bool isCollidedPlayer() const;

	// 攻撃を受けたか
	const bool isDamaged() const;

private:

	// ゴミの生成処理
	void generateTrash();

	// 生成範囲
	const Box& m_fieldArea;

	// プレイヤーのインスタンス
	const PlayerCharacter& m_playerInstance;

	// プレイヤーとゴミの接触
	bool m_isCollided;

	// ゴミが攻撃された
	bool m_isDamaged;

	// 生成タイマー
	double m_generateTimer;

	// 片付けたゴミの数
	uint8 m_deletedTrashCount;

	// unique_ptrの配列
	Array<std::unique_ptr<TrashObject>> m_trashObjectArray;
};
