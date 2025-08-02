// CameraController class

#include "CameraController.hpp"

using namespace Config::Camera;

CameraController::CameraController(BasicCamera3D& camera)
	: m_camera{ camera }
	, m_eyePosition{ camera.getEyePosition() }
	, m_theta{ 0.0 }
	, m_phi{ 0.0 }
{

}

void CameraController::update(const double deltaTime, const Vec3 playerPosition)
{
	// カメラの回転
	rotateCamera(deltaTime);

	// カメラ位置の更新
	m_camera.setView(playerPosition + m_eyePosition, playerPosition);
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
	m_theta -= mouseDelta.y;
	m_phi -= mouseDelta.x;

	// θ角をクランプ
	m_theta = Clamp(m_theta, 30_deg, 85_deg);

	// 球面座標からカメラ座標を計算
	m_eyePosition = Spherical{ CameraDistance, m_theta, m_phi };
}
