// TrashObject class

# include "TrashObject.hpp"

using namespace Config::Player::AttackForce;
using namespace Config::Scene::Field;

TrashObject::TrashObject(const Vec3& position, const Model& model, const PlayerCharacter& instance, const Box& fieldArea)
	: m_playerInstance{ instance }
	, m_model{ model }
	, m_fieldArea{ fieldArea }
	, m_effect{}
	, m_position{ position }
	, m_velocity{ Vec3::Zero() }
	, m_rotation{ Random(360_deg) }
	, m_prevDamaged{ false }
	, m_isDamaged{ false }
	, m_prevOutside{ false }
{

}

void TrashObject::update(const double deltaTime)
{
	// 現在のモデルデータをキャッシュ
	const Model& currentPlayerModel{ m_playerInstance.getCurrentModel() };
	m_isDamaged = isDamaged(currentPlayerModel);

	if (m_isDamaged && !m_prevDamaged)
	{
		m_velocity = Vec3::Zero();
		Vec3 addForce{ Vec3::Zero()};

		const Quaternion playerRotation{ m_playerInstance.getPlayerRotation() };

		if (currentPlayerModel == ModelAssets::GetInstance().attackingModelArray[0] ||
			currentPlayerModel == ModelAssets::GetInstance().attackingModelArray[1])
		{
			// 弱一段と二段
			addForce = LightAttack * playerRotation;
			AudioAsset(Assets::DamageLite).playOneShot();
		}
		else
		{
			if (currentPlayerModel == ModelAssets::GetInstance().attackingModelArray[2])
			{
				// 弱三段
				addForce = LightFinish * playerRotation;
			}
			else if (currentPlayerModel == ModelAssets::GetInstance().attackingModelArray[3])
			{
				// 弱一段 -> 強派生
				addForce = Uppercut * playerRotation;
			}
			else
			{
				// 弱二段 -> 強派生
				addForce = Kick * playerRotation;
			}

			AudioAsset(Assets::DamageHeavy).playOneShot(0.4);
		}
		m_velocity += addForce;
	}
	else
	{
		const float gravity{ 45.0f };
		m_velocity.y -= gravity * deltaTime;
		if (m_velocity.y < -gravity)
		{
			m_velocity.y = -gravity;
		}

		const float friction{ 0.98f };
		m_velocity.x *= friction;
		m_velocity.z *= friction;

		if (isCollidedPlayer())
		{
			const Vec3 moveVector{ Vec3::Forward() * m_playerInstance.getPlayerRotation() };
			m_velocity = moveVector;
		}

		const Box tableCollider{ Box::FromPoints(Vec3{ -16, 0, -16 }, Vec3{ 16, -2, 16 }) };
		if (m_model.boundingBox().movedBy(m_position).intersects(tableCollider))
		{
			m_velocity.y = 0;
			m_position.y = 0;
		}
	}

	// 直前の被弾をキャッシュ
	m_prevDamaged = isDamaged(currentPlayerModel);

	// 直前の場外をキャッシュ
	m_prevOutside = !m_fieldArea.intersects(m_model.boundingBox().movedBy(m_position));

	// モデルを速度に従って移動
	m_position.moveBy(m_velocity * deltaTime);
}

void TrashObject::draw() const
{
	m_model.draw(m_position, Quaternion::RotateY(m_rotation));
}

const bool TrashObject::isDamaged(const Model& model) const
{
	// 現在のアニメーションのコマが、攻撃判定を持っているか判定
	const bool isAttacking{ ModelAssets::GetInstance().attackingModelArray.contains(model) };

	// 攻撃範囲内にいるか判定
	const bool canHit{ m_model.boundingBox().movedBy(m_position).intersects(m_playerInstance.getAttackCollider()) };

	// 両方揃ったら被弾
	return isAttacking && canHit;
}

const bool TrashObject::isCollidedPlayer() const
{
	return m_model.boundingBox().movedBy(m_position).intersects(m_playerInstance.getOutsideCollider());
}

const bool TrashObject::getIsDamaged() const
{
	return m_isDamaged;
}

const bool TrashObject::isOutside() const
{
	const bool isOutside{ !m_fieldArea.intersects(m_model.boundingBox().movedBy(m_position)) };

	// 場外に出た瞬間だけtrue
	return isOutside && !m_prevOutside;
}

const bool TrashObject::isGrounded() const
{
	return m_position.y < FloorHeight;
}
