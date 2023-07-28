#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Beam {
public:
	// コンストラクタ
	Beam();
	// デストラクタ
	~Beam();
	// 初期化
	void Initialize(ViewProjection viewProjection, Player* player);
	// 更新
	void Update();
	// 3D描画
	void Draw3D();
	// インプットクラス
	Input* input_ = nullptr;
	void Born();
	void Move();
	int GetFlag_() { return BeamFlag_; }
	float GetX() { return worldTransformBeam_.translation_.x; }
	float GetY() { return worldTransformBeam_.translation_.y; }
	float GetZ() { return worldTransformBeam_.translation_.z; }

private:
	ViewProjection viewProjection_;
	// ビーム
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = nullptr;
	WorldTransform worldTransformBeam_;
	int BeamTimer_ = 0;
	int BeamFlag_;
	Player* player_ = nullptr;
};