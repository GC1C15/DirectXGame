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
	void Initialize(ViewProjection viewProjection);
	// 更新
	void Update();
	// 3D描画
	void Draw3D();
	// インプットクラス
	Input* input_ = nullptr;
	void Born();
	void Move();
	void Jump();

private:
	ViewProjection viewProjection_;
	// ビーム
	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	WorldTransform worldTransformEnemy_[10];
	float enemySpeed_[10] = {};
	int EnemyFlag_[10];
	float enemyJumpSpeed_[10] = {};
	int gameTimer_ = 0;
};