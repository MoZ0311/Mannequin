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
};
