// PlayerCharacter class

# include "PlayerCharacter.hpp"

using namespace Config::Player;

PlayerCharacter::PlayerCharacter()
	: m_modelAssets{ ModelAssets::GetInstance() }
	, m_playerPosition{ 0.0, 0.0, 0.0 }
	, m_playerRotation{ 0.0, 0.0, 0.0, 1.0 }
	, m_animationArray{ ModelAssets::GetInstance().idleAnimationArray }
	, m_attackInputBuffer{}
	, m_animationTimer{ 0.0 }
	, m_actionState{ ActionState::None }
	, m_hasAttacked{ true }
{

}

void PlayerCharacter::update(const double deltaTime, const Vec3& cameraForward, const Box& fieldArea)
{	
	move(deltaTime, cameraForward, fieldArea);	
	handleAttackInput();
	updateActionState();
	updateAnimation();
}

void PlayerCharacter::draw() const
{
	// double型のタイマーを切り捨てて整数値に
	uint8 index{ static_cast<uint8>(Floor(m_animationTimer)) };

	// 対応するアニメーション配列のモデルを描画
	m_animationArray[index].draw(m_playerPosition, m_playerRotation);

	// 影の描画
	const Disc shadow{ Vec3{m_playerPosition.x, 0.0001, m_playerPosition.z}, m_modelAssets.mannequinRest.boundingSphere().r / 2 };
	shadow.draw(ColorF{0, 0, 0, 0.5});

	// debug
	const float length{ m_animationArray == m_modelAssets.heavyAttackAnimationArray02 ? 0.75f : 0.5f };
	const Vec3& offset{ Vec3::Forward(length) * m_playerRotation };
	m_modelAssets.mannequinCollider.movedBy(m_playerPosition + offset).draw(m_playerRotation, ColorF{ 1.0, 0.0, 0.0, 0.5 });	// 攻撃判定

	m_modelAssets.mannequinCollider.movedBy(m_playerPosition).draw(m_playerRotation, ColorF{ 0.0, 1.0, 0.0, 0.5 });	// 本人のアタリ判定
}

void PlayerCharacter::move(const double deltaTime, const Vec3& cameraForward, const Box& fieldArea)
{
	// 平面移動ベクトル(x : 左右, y : 前後)
	const Vec2& movementVector2D{ PlayerInput::GetMovementAxis() };

	// 移動入力がなければそのままreturn
	if (movementVector2D.isZero() || PlayerInput::KeyGuard())
	{
		return;
	}

	// カメラの向きを基準にした右向きベクトル
	const Vec3& rightVector{ -cameraForward.cross(Vec3::Up()).normalized() };

	// 空間移動ベクトル
	const Vec3& velocity{ movementVector2D.y * cameraForward + movementVector2D.x * rightVector };

	// 念の為0ベクトルでないかのチェック
	if (!velocity.isZero())
	{
		// Y軸回転角度を計算
		const double angleY{ Atan2(velocity.x, velocity.z) };

		if (m_actionState != ActionState::None)
		{
			if (m_animationTimer < Scene::DeltaTime())
			{
				// 攻撃の出始めに自由な方向へ即時方向転換可能
				m_playerRotation = Quaternion::RotateY(angleY);
			}
			// 出始め以降は回転も移動も不可
			return;
		}

		// 線形補正をかけながらプレイヤーを回転
		m_playerRotation = m_playerRotation.slerp(Quaternion::RotateY(angleY), RotateSpeed * deltaTime);
	}

	// ダッシュ中かの判定
	const float moveSpeed{ PlayerInput::KeyDash() ? MoveSpeed::Sprint : MoveSpeed::Default };

	// 直前の自身の座標をキャッシュ
	const Vec3 prevPosition{ m_playerPosition };

	// モデル描画位置を移動
	m_playerPosition.moveBy(velocity * moveSpeed * deltaTime);

	// エリアからはみ出したとき、直前座標に戻す
	if (!fieldArea.contains(m_modelAssets.mannequinBoundingBox.oriented(m_playerRotation).movedBy(m_playerPosition)))
	{
		m_playerPosition = prevPosition;
	}
}

void PlayerCharacter::handleAttackInput()
{
	// コマンドに対応したアニメーションを蓄積
	if (m_attackInputBuffer.size() < MaxBufferSize)
	{
		if (PlayerInput::KeyHeavyAttack())
		{
			// 強攻撃をキューに追加
			switch (m_actionState)
			{
			case ActionState::None:		// 非攻撃状態 -> 強派生
				m_actionState = ActionState::None;
				m_attackInputBuffer.push(m_modelAssets.liteAttackAnimationArray03);
				break;

			case ActionState::Lite01:	// 弱一段 -> 強派生
				m_actionState = ActionState::Heavy01;
				m_attackInputBuffer.push(m_modelAssets.heavyAttackAnimationArray01);
				break;

			case ActionState::Lite02:	// 弱二段 -> 強派生
				m_actionState = ActionState::Heavy02;
				m_attackInputBuffer.push(m_modelAssets.heavyAttackAnimationArray02);
				break;

			default:
				break;
			}
		}
		else if (PlayerInput::KeyLiteAttack())
		{
			// 弱攻撃をキューに追加
			switch (m_actionState)
			{
			case ActionState::None:		// 非攻撃状態 -> 弱一段
				m_actionState = ActionState::Lite01;
				m_attackInputBuffer.push(m_modelAssets.liteAttackAnimationArray01);
				break;

			case ActionState::Lite01:	// 弱一段 -> 弱二段
				m_actionState = ActionState::Lite02;
				m_attackInputBuffer.push(m_modelAssets.liteAttackAnimationArray02);
				break;

			case ActionState::Lite02:	// 弱二段 -> 弱三段
				m_actionState = ActionState::Lite03;
				m_attackInputBuffer.push(m_modelAssets.liteAttackAnimationArray03);
				break;

			default:
				break;
			}
		}
	}
}

void PlayerCharacter::updateActionState()
{
	// 攻撃モーションが終わっている
	if (m_hasAttacked)
	{
		// バッファが空でない
		if (!m_attackInputBuffer.empty())
		{
			m_animationArray = m_attackInputBuffer.front();
			m_attackInputBuffer.pop();

			m_animationTimer = 0;
			m_hasAttacked = false;

			if (m_animationArray == m_modelAssets.heavyAttackAnimationArray02)
			{
				AudioAsset(Assets::BlowHeavy).playOneShot();
			}
			else
			{
				AudioAsset(Assets::BlowLite).playOneShot();
			}
		}
		else if (PlayerInput::KeyGuard())
		{
			// ガード中である
			m_animationArray = m_modelAssets.guardAnimationArray;
		}
		else if (PlayerInput::GetMovementAxis().isZero())
		{
			// 停止中である
			m_animationArray = m_modelAssets.idleAnimationArray;
		}
		else
		{
			// 攻撃中でもガード中でも停止中でもない -> 移動中である
			m_animationArray = m_modelAssets.walkAnimationArray;
		}
	}
}

void PlayerCharacter::updateAnimation()
{
	// アニメーション用のタイマーをカウントアップ
	const float animationSpeed{ m_actionState == ActionState::None ? AnimationSpeed::Default : AnimationSpeed::Attack };
	m_animationTimer += Scene::DeltaTime() * animationSpeed;

	// 配列の要素数を超える時、リセット
	if (m_animationTimer >= m_animationArray.size())
	{
		m_animationTimer = 0;
		m_hasAttacked = true;

		if (m_attackInputBuffer.empty())
		{
			// バッファが空であれば、コンボ終了でリセット
			m_actionState = ActionState::None;
		}
	}
}

Vec3 PlayerCharacter::getPlayerPosition() const
{
	// 基本姿勢の中心点を返す
	return m_modelAssets.mannequinCollider.movedBy(m_playerPosition).oriented(m_playerRotation).center;
}

Quaternion PlayerCharacter::getPlayerRotation() const
{
	return m_playerRotation.normalized();
}
