// ModelAssets class

# pragma once

# include "../core/Config.hpp"

class ModelAssets
{
private:

	// コンストラクタ
	ModelAssets();

	const Model m_mannequinIdle01;
	const Model m_mannequinIdle02;
	const Model m_mannequinIdle03;

	const Model m_mannequinWalk01;
	const Model m_mannequinWalk02;
	const Model m_mannequinWalk03;
	const Model m_mannequinWalk04;
	const Model m_mannequinWalk05;
	const Model m_mannequinWalk06;
	const Model m_mannequinWalk07;
	const Model m_mannequinWalk08;

	const Model m_mannequinLiteAttack01;
	const Model m_mannequinLiteAttack02;
	const Model m_mannequinLiteAttack03;
	const Model m_mannequinLiteAttack04;

	const Model m_mannequinLiteAttack05;
	const Model m_mannequinLiteAttack06;
	const Model m_mannequinLiteAttack07;

	const Model m_mannequinLiteAttack08;
	const Model m_mannequinLiteAttack09;
	const Model m_mannequinLiteAttack10;

	const Model m_mannequinHeavyAttack01;
	const Model m_mannequinHeavyAttack02;
	const Model m_mannequinHeavyAttack03;
	const Model m_mannequinHeavyAttack04;

	const Model m_mannequinHeavyAttack05;
	const Model m_mannequinHeavyAttack06;
	const Model m_mannequinHeavyAttack07;
	const Model m_mannequinHeavyAttack08;
	const Model m_mannequinHeavyAttack09;

	const Model m_mannequinGuard;

public:

	// インスタンスの取得
	static ModelAssets& GetInstance();

	// 9Pコーワのモデル
	const Model qpKowa;

	// 棒立ち状態のモデル
	const Model mannequinRest;

	// マネキンの当たり判定
	const Box mannequinInsideCollider;

	// マネキンの外側判定
	const Box mannequinOutsideCollider;

	// 待機アニメーション配列
	const Array<Model> idleAnimationArray;

	// 歩行アニメ―ション配列
	const Array<Model> walkAnimationArray;

	// 弱1アニメーション配列
	const Array<Model> liteAttackAnimationArray01;

	// 弱2アニメーション配列
	const Array<Model> liteAttackAnimationArray02;

	// 弱3アニメーション配列
	const Array<Model> liteAttackAnimationArray03;

	// 弱1強派生アニメーション配列
	const Array<Model> heavyAttackAnimationArray01;

	// 弱2強派生アニメーション配列
	const Array<Model> heavyAttackAnimationArray02;

	// ガードアニメーション配列
	const Array<Model> guardAnimationArray;

	// 攻撃判定を持つモデルの配列
	const Array<Model> attackingModelArray;
};
