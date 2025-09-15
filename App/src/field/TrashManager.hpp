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
	void update(const double deltaTime);

	// 描画処理
	void draw() const;

private:

	// ゴミの生成処理
	void generateTrash();

	// 生成範囲
	const Box& m_fieldArea;

	// 生成タイマー
	double m_generateTimer;

	// unique_ptrの配列
	Array<std::unique_ptr<TrashObject>> m_trashObjectArray;
};
