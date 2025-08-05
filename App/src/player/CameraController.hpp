// CameraController class

#pragma once

# include "../core/Config.hpp"
# include "../player/PlayerInput.hpp"

class CameraController
{
public:

	// コンストラクタ
	CameraController(BasicCamera3D& camera);

	// 更新処理
	void update(const double deltaTime, const Vec3 playerPosition);

	// カメラの前方ベクトル(y = 0)を取得
	Vec3 getCameraForward() const;

private:

	// カメラの回転処理
	void rotateCamera(const double deltaTime);

	// カメラのアドレス
	BasicCamera3D& m_camera;

	// カメラ位置
	Vec3 m_eyePosition;

	// カメラのトランジション
	Transition m_cameraTransition;

	// 球面座標系のθ
	double m_theta;

	// 球面座標系のφ
	double m_phi;
};
