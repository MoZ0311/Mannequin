// PlayerCharacter class

# pragma once

# include "PlayerInput.hpp"
# include "../util/Util.hpp"
# include "../core/ModelAssets.hpp"

enum class ActionState
{
	None,
	Lite01,
	Lite02,
	Lite03,
	Heavy01,
	Heavy02,
};

class PlayerCharacter
{
public:

	// コンストラクタ
	PlayerCharacter(const Box& fieldArea);

	// 更新処理
	virtual void update(const double deltaTime, const Vec3& cameraForward, const bool isCollided);

	// 描画処理
	void draw() const;

	// プレイヤー座標の取得
	const Vec3 getPlayerPosition() const;

	// プレイヤーの向きの取得
	const Quaternion getPlayerRotation() const;

	// プレイヤーの内側コライダー取得
	const OrientedBox getInsideCollider() const;

	// プレイヤーの外側コライダー取得
	const OrientedBox getOutsideCollider() const;

	// プレイヤーの攻撃用コライダー取得
	const OrientedBox getAttackCollider() const;

	// プレイヤーの現在のモデル取得
	const Model& getCurrentModel() const;

private:

	// 移動処理
	void move(const double deltaTime, const Vec3& cameraForward, const bool isCollided);

	// 攻撃コマンドの蓄積処理
	void handleAttackInput();

	// プレイヤーの状態の更新
	void updateActionState();

	// アニメーション更新処理
	void updateAnimation();

	// モデルアセットクラスのインスタンス
	const ModelAssets& m_modelAssets;

	// 行動範囲
	const Box& m_fieldArea;

	// プレイヤーの位置
	Vec3 m_playerPosition;

	// プレイヤーの回転
	Quaternion m_playerRotation;

	// アニメーション配列
	Array<Model> m_animationArray;

	// 攻撃アニメーションのバッファ
	std::queue<Array<Model>> m_attackInputBuffer;

	// アニメーション配列のインデックス
	uint8 m_animationIndex;

	// アニメーション制御用のタイマー
	double m_animationTimer;

	// プレイヤーの状態
	ActionState m_actionState;

	// 攻撃後であるか
	bool m_hasAttacked;
};
