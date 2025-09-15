// Unitbase class

# pragma once

# include "../player/PlayerCharacter.hpp"

class UnitBase : public PlayerCharacter
{
public:

	// コンストラクタ
	UnitBase();

	// 更新処理
	void update(const double deltaTime, const Vec3& cameraForward, const Box& fieldBox) override;

	// 描画処理
	void drawUI() const;

	uint8 getMaxHp() const;

	uint8 getCurrentHp() const;

	String getUnitName() const;

protected:

	// 移動処理
	void move(const double deltaTime, const Vec3& cameraForward);

	// 行動開始時点のユニット座標
	Vec3 m_startPosition;

	// 直前のユニット座標
	Vec3 m_prevPosition;

	// 移動範囲の半径
	float m_moveRangeRadius;

	// 攻撃範囲の半径
	float m_attackRangeRadius;

	bool m_hasMoved;

	bool m_completedAction;

	// 最大HP
	uint8 m_maxHp;

	// 現在HP
	uint8 m_currentHp;

	// ユニット名
	String m_unitName;
};
