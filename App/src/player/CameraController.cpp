// CameraController class

#include "CameraController.hpp"

using namespace Config::Camera;

CameraController::CameraController(BasicCamera3D& camera)
	: m_camera{ camera }
	, m_eyeOffset{ camera.getEyePosition() }
	, m_cameraDistance{ Distance::Near }
	, m_theta{ Pitch::Default }
	, m_phi{ 180_deg }
{

}

void CameraController::update(const double deltaTime, const Vec3& playerPosition, const Quaternion& playerRotation)
{
	// カメラの回転
	rotateCamera(deltaTime);

	// カメラ距離の計算
	m_cameraDistance = PlayerInput::KeyDash() && !PlayerInput::GetMovementAxis().isZero() ? Distance::Far : Distance::Near;

	// カメラのリセット
	if (PlayerInput::ResetCamera())
	{
		m_theta = Pitch::Default;
		m_phi = normalizePlayerRotation(playerRotation); 
	}

	// カメラ位置の更新
	const Vec3& eyePosition{ m_camera.getEyePosition().lerp(playerPosition + m_eyeOffset, Interpolation) };
	m_camera.setView(eyePosition, playerPosition);
}

Vec3 CameraController::getCameraForward() const
{
	// カメラ位置から注視点へのベクトルを取得
	Vec3 lookAtVector{ m_camera.getLookAtVector() };

	// 高さ成分を0に
	lookAtVector.y = 0;

	// 正規化してreturn
	return lookAtVector.normalize();
}

void CameraController::rotateCamera(const double deltaTime)
{
	// カーソルの移動量を取得
	const Vec2& mouseDelta{ PlayerInput::GetCameraAxis() * deltaTime };

	// θ角とφ角を更新
	m_theta += mouseDelta.y;
	m_phi += mouseDelta.x;

	// θ角をクランプ
	m_theta = Clamp(m_theta, Pitch::Min, Pitch::Max);

	// 球面座標からカメラ座標を計算
	m_eyeOffset = Spherical{ m_cameraDistance, m_theta, m_phi + RotateOffset };
}

double CameraController::normalizePlayerRotation(const Quaternion& playerRotation) const
{
	// プレイヤーの回転をオイラー角に変換
	const Vec3& playerEuler{ Util::QuaternionToEuler(playerRotation) };

	// ヨー角
	double playerYaw{ playerEuler.y };

	// プレイヤー角度の正規化
	if (playerEuler.xz().isZero())
	{
		playerYaw -= 180_deg;
	}
	else
	{
		if (playerYaw < 0_deg)
		{
			playerYaw += 360_deg;
		}
	}

	return Abs(playerYaw);
}
