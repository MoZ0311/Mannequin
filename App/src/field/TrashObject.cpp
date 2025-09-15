// TrashObject class

# include "TrashObject.hpp"

TrashObject::TrashObject(const Vec3& position, const Model& model, const PlayerCharacter& instance)
	: m_playerInstance{ instance }
	, m_model{ model }
	, m_effect{}
	, m_position{ position }
	, m_velocity{ Vec3::Zero() }
	, m_rotation{ Random(360_deg) }
{

}

void TrashObject::update(const double deltaTime)
{
	// 現在のモデルデータをキャッシュ
	const Model& currentModel{ m_playerInstance.getCurrentModel() };

	if (isDamaged(currentModel))
	{
		Vec3 addForce{ Vec3::Zero()};

		if (currentModel == ModelAssets::GetInstance().attackingModelArray[5] ||
			currentModel == ModelAssets::GetInstance().attackingModelArray[6])
		{
			// 弱二段 -> 強派生
			addForce = Vec3{ 0.0, 120.0, 1500 } * m_playerInstance.getPlayerRotation();
		}
		else if (currentModel == ModelAssets::GetInstance().attackingModelArray[4])
		{
			// 弱一段 -> 強派生 の本当て
			addForce = Vec3{ 0.0, 200, 600 } * m_playerInstance.getPlayerRotation();
		}
		else if (currentModel == ModelAssets::GetInstance().attackingModelArray[3])
		{
			// 弱一段 -> 強派生 のカス当て
			addForce = -Vec3::Forward() * m_playerInstance.getPlayerRotation();
		}
		else if (currentModel == ModelAssets::GetInstance().attackingModelArray[2])
		{
			// 弱三段
			addForce = Vec3{ 0.0, 50.0, 600.0 } *m_playerInstance.getPlayerRotation();
		}
		else
		{
			// 弱一段と二段
			addForce = Vec3{ 0.0, 0.1, -0.2} * m_playerInstance.getPlayerRotation();
		}
		m_velocity += addForce;
	}
	else
	{
		m_velocity.y -= 9.81f;
		if (m_velocity.y < -25.0f)
		{
			m_velocity.y = -25.0f;
		}
		m_velocity.x *= 0.75f;
		m_velocity.z *= 0.75f;

		if (isCollidedPlayer())
		{
			const Vec3 moveVector{ Vec3::Forward() * m_playerInstance.getPlayerRotation() };
			m_velocity = moveVector;
		}
		if (m_model.boundingBox().movedBy(m_position).intersects(Box::FromPoints(Vec3{ -16, 0, -16 }, Vec3{ 16, -2, 16 })))
		{
			m_velocity.y = -0.001f;
			m_position.y = 0;
		}
	}

	m_position.moveBy(m_velocity / 2 * deltaTime);
}

void TrashObject::draw() const
{
	m_model.draw(m_position, Quaternion::RotateY(m_rotation));
}

const bool TrashObject::isCollidedPlayer() const
{
	return m_model.boundingBox().movedBy(m_position).intersects(m_playerInstance.getOutsideCollider());
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

const bool TrashObject::isGrounded() const
{
	return m_position.y < -19;
}
