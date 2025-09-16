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
	void update(const uint8 deletedCount);

	// 描画処理
	void draw() const;

private:

	// ステータスウィンドウ
	const Rect m_characterStatus;

	// スコア
	uint8 m_score;
};
