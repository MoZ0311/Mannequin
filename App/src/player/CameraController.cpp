// CameraController class

#include "CameraController.hpp"

using namespace Config::Camera;

CameraController::CameraController(BasicCamera3D& camera)
	: m_camera{ camera }
	, m_eyePosition{ camera.getEyePosition() }
	, m_cameraTransition{ 0.3s }
	, m_theta{ 75_deg }
	, m_phi{ 180_deg }
{

}

void CameraController::update(const double deltaTime, const Vec3 playerPosition, const Quaternion playerRotation)
{
	// カメラの回転
	rotateCamera(deltaTime);

	const Vec3 playerEuler{ Util::QuaternionToEuler(playerRotation) };
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
	playerYaw = Abs(playerYaw);

	// カメラのリセット
	if (PlayerInput::ResetCamera())
	{
		m_theta = 75_deg;
		m_phi = playerYaw; 
	}

	// カメラ位置の更新
	m_camera.setView(playerPosition + m_eyePosition, playerPosition);

	Print << Math::ToDegrees(m_phi);
	Print << Math::ToDegrees(playerYaw);
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
	const Vec2 mouseDelta{ PlayerInput::GetCameraAxis() * deltaTime };

	// θ角とφ角を更新
	m_theta += mouseDelta.y;
	m_phi += mouseDelta.x;

	// θ角をクランプ
	m_theta = Clamp(m_theta, Pitch::Min, Pitch::Max);

	// ダッシュ入力中か判定
	m_cameraTransition.update(PlayerInput::KeyDash() && !PlayerInput::GetMovementAxis().isZero());

	// カメラ距離にイースをつける
	const double e = EaseOutExpo(m_cameraTransition.value());
	const double cameraDistance{ Distance::Near + e * 2 };

	// 球面座標からカメラ座標を計算
	m_eyePosition = Spherical{ cameraDistance, m_theta, m_phi + 90_deg };
}
