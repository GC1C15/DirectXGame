#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player {
public:
	Player();
	~Player();

	void Initialize(ViewProjection viewProjection);
	void Update();
	void Draw3D();

	void Start();

	float GetX() { return worldTransformPlayer_.translation_.x; }
	float GetY() { return worldTransformPlayer_.translation_.y; }
	float GetZ() { return worldTransformPlayer_.translation_.z; }

private:
	ViewProjection viewProjection_;

	uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;

	Input* input_ = nullptr;

	int playerTimer_ = 60;
};