// UIDrawer class

# pragma once

# include "../core/Config.hpp"

class UIDrawer
{
public:

	// コンストラクタ
	UIDrawer();

	// デストラクタ
	~UIDrawer();

	// 更新処理
	void update(const double deltaTime);

	// 描画処理
	void draw() const;

private:

	// ステータスウィンドウ
	const Rect m_characterStatus;

	// ユニット名
	String m_unitName;

	// ユニットの最大体力
	uint8 m_maxUnitHp;

	// ユニットの現在体力
	uint8 m_currentUnitHp;
};
