// TrashGenerator class

# pragma once

# include <memory>
# include "TrashObject.hpp"
# include "../core/ModelAssets.hpp"

class TrashManager
{
public:

	// コンストラクタ
	TrashManager(const Box& fieldArea);

	// 更新処理
	void update(const double deltaTime, const OrientedBox& collider);

	// 描画処理
	void draw() const;

	// 接触したか
	const bool isCollidedPlayer() const;

private:

	// ゴミの生成処理
	void generateTrash(const OrientedBox& collider);

	// 生成範囲
	const Box& m_fieldArea;

	// プレイヤーとゴミの接触
	bool m_isCollided;

	// 生成タイマー
	double m_generateTimer;

	// unique_ptrの配列
	Array<std::unique_ptr<TrashObject>> m_trashObjectArray;
};
