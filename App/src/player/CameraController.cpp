// CameraController class

#include "CameraController.hpp"

CameraController::CameraController(BasicCamera3D& camera)
	: m_camera{ camera }
	, m_eyePosition{ camera.getEyePosition() }
{

}

void CameraController::Update(const Vec3& playerPosition)
{
	m_camera.setView(playerPosition + m_eyePosition, playerPosition);
}

Vec3 CameraController::GetCameraForward() const
{
	Vec3 lookAtVector = m_camera.getLookAtVector();
	lookAtVector.y = 0;
	lookAtVector.normalize();

	return lookAtVector;
}

void CameraController::SetEyePosition(const Vec3& position)
{
	m_eyePosition = position;
}
