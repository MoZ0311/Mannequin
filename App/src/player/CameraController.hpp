// CameraController class

#pragma once

class CameraController
{
public:

	// コンストラクタ
	CameraController(BasicCamera3D& camera);

	void Update(const Vec3& playerPosition);

	Vec3 GetCameraForward() const;
	void SetEyePosition(const Vec3& position);

private:

	BasicCamera3D& m_camera;
	Vec3 m_eyePosition;
};
