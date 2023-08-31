#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <time.h>

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize(ViewProjection viewProjection);
	void Update(int gameTimer);
	void Draw3D();
	void Move(int gameTimer);
	void Born();
	float GetX() { return worldTransformEnemy_.translation_.x; }
	float GetZ() { return worldTransformEnemy_.translation_.z; }
	int GetFlag() { return aliveFlag_; }
	void Hit() { aliveFlag_ = 2; }
	void JumpHit() { jumpSpeed_ = 1; };
	void Start();
	void Jump();

private:
	ViewProjection viewProjection_;

	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	WorldTransform worldTransformEnemy_;

	Input* input_ = nullptr;

	int aliveFlag_ = 0;

	float xSpeed_ = 0;

	float jumpSpeed_ = 0;
};