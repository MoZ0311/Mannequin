// TrashGenerator class

# pragma once

# include <memory>
# include "TrashObject.hpp"

class TrashGenerator
{
public:

	// コンストラクタ
	TrashGenerator();

	// 更新処理
	void update(const double deltaTime, const Box& fieldArea);

	// 描画処理
	void draw() const;

private:

	// ゴミの生成処理
	void generateTrash(const Box& fieldArea);

	// 生成タイマー
	double m_generateTimer;

	// unique_ptrの配列
	Array<std::unique_ptr<TrashObject>> m_trashObjectArray;
};
