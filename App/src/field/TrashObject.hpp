// TrashObject class

# pragma once

class TrashObject
{
public:

	// コンストラクタ
	TrashObject(const Vec3& position, const Model& model);

	// 更新処理
	void update(const double deltaTime);

	// 描画処理
	void draw() const;

protected:

	// 現在位置
	Vec3 m_position;

	// 現在の回転
	const double m_rotation;

	// モデル
	const Model m_model;
};
