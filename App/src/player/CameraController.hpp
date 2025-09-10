// CameraController class

# pragma once

# include "../core/Config.hpp"
# include "../player/PlayerInput.hpp"
# include "../util/Util.hpp"

class CameraController
{
public:

	// コンストラクタ
	CameraController(BasicCamera3D& camera);

	// 更新処理
	void update(const double deltaTime, const Vec3& playerPosition, const Quaternion& playerRotation);

	// カメラの前方ベクトル(y = 0)を取得
	Vec3 getCameraForward() const;

private:

	// カメラの回転処理
	void rotateCamera(const double deltaTime);

	// プレイヤーの回転角度の正規化処理
	double normalizePlayerRotation(const Quaternion& playerRotation) const;

	// カメラのアドレス
	BasicCamera3D& m_camera;

	// カメラ位置
	Vec3 m_eyeOffset;

	// プレイヤーとカメラの距離
	float m_cameraDistance;

	// 球面座標系のθ
	double m_theta;

	// 球面座標系のφ
	double m_phi;
};
