#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy {
public:
	// コンストラクタ
	Enemy();
	// デストラクタ
	~Enemy();
	// 初期化
	void Initialize(ViewProjection viewProjection, Enemy* enemy);
	// 更新
	void Update();
	// 3D描画
	void Draw3D();
	// インプットクラス
	Input* input_ = nullptr;
	void Born();
	void Move();
	void Jump();
	int GetFlag_() { return EnemyFlag_; }
	void Hit() { isAlive_ = 0; }
	float GetX() { return worldTransformEnemy_.translation_.x; }
	float GetY() { return worldTransformEnemy_.translation_.y; }
	float GetZ() { return worldTransformEnemy_.translation_.z; }


private:
	ViewProjection viewProjection_;
	// ビーム
	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	Enemy* enemy_ = nullptr;
	WorldTransform worldTransformEnemy_;
	float enemySpeed_ = {};
	int EnemyFlag_;
	int isAlive_;
	float enemyJumpSpeed_ = 3;
	int gameTimer_ = 0;
};