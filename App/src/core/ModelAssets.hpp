// ModelAssets class

#pragma once

class ModelAssets
{
private:

	// コンストラクタ
	ModelAssets();

	const Model mannequinIdle01;
	const Model mannequinIdle02;
	const Model mannequinIdle03;

	const Model mannequinWalk01;
	const Model mannequinWalk02;
	const Model mannequinWalk03;
	const Model mannequinWalk04;
	const Model mannequinWalk05;
	const Model mannequinWalk06;
	const Model mannequinWalk07;
	const Model mannequinWalk08;

	const Model mannequinLiteAttack01;
	const Model mannequinLiteAttack02;
	const Model mannequinLiteAttack03;
	const Model mannequinLiteAttack04;

	const Model mannequinLiteAttack05;
	const Model mannequinLiteAttack06;
	const Model mannequinLiteAttack07;

	const Model mannequinLiteAttack08;
	const Model mannequinLiteAttack09;
	const Model mannequinLiteAttack10;

	const Model mannequinHeavyAttack01;
	const Model mannequinHeavyAttack02;
	const Model mannequinHeavyAttack03;
	const Model mannequinHeavyAttack04;

	const Model mannequinGuard;

public:

	// インスタンスの取得
	static ModelAssets& GetInstance();

	// 棒立ち状態のモデル
	const Model mannequinRest;

	// マネキンの当たり判定
	const Box mannequinCollider;

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

	// ガードアニメーション配列
	const Array<Model> guardAnimationArray;
};
