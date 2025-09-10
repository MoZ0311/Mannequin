// UnitManager class

# pragma once

# include "../core/Config.hpp"
# include "UnitSword.hpp"
# include "UnitArcher.hpp"

class UnitManager
{
public:

	// インスタンスのゲッター
	static UnitManager* GetInstance();

	// 破棄処理
	static void Release();

	// 更新処理
	void update(double deltaTime, Vec3 cameraForward);

	// 描画処理
	void draw() const;

	// インデックスのユニット情報取得
	UnitBase* getUnitData(uint8 index) const;

	// 選択中ユニットインデックスの取得
	uint8 getUnitIndex() const;

private:

	// コンストラクタ
	UnitManager();

	// デストラクタ
	~UnitManager();

	// 消去
	void resetUnitArray();

	// ユニット生成
	void createUnits();

	// シングルトンのインスタンス
	static UnitManager* instance;

	// 自軍配列
	Array<UnitBase*> m_playerUnitArray;

	// 敵軍配列
	Array<UnitBase*> m_enemyUnitArray;

	// 全軍配列
	Array<UnitBase*> m_allUnitArray;

	// 選択中ユニットのインデックス
	uint8 m_selectedUnitIndex;
};
