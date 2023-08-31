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
	Beam();
	~Beam();

	void Initialize(ViewProjection viewProjection, Player* player);
	void Update();
	void Draw3D();
	void Move();
	void Born();
	float GetX() { return worldTransformBeam_.translation_.x; }
	float GetZ() { return worldTransformBeam_.translation_.z; }
	int GetFlag() { return aliveFlag_; }
	void Hit() { aliveFlag_ = 0; }
	void Start();

private:
	ViewProjection viewProjection_;

	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = nullptr;
	WorldTransform worldTransformBeam_;

	Input* input_ = nullptr;

	int aliveFlag_ = 0;

	Player* player_ = nullptr;
};
