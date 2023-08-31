#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugText.h"
#include "Stage.h"
#include "Player.h"
#include "Beam.h"
#include "Enemy.h"
class GamePlay {
public:
	// コンストラクタ
	GamePlay();
	// デストラクタ
	~GamePlay();
	// 初期化
	void Initialize(ViewProjection viewProjection);
	// 更新
	void Update();
	// 3D描画
	void Draw3D();
	// 2D背景描画
	void Draw2DFar();
	// 2D前背景描画
	void Draw2DNear();
	// 衝突判定
	void collision();
	// 敵とプレイヤーの衝突判定
	void collisionPlayerEnemy();
	// ビームと敵の衝突判定
	void collisionBeamEnemy();
private:
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
	Stage* stage_ = nullptr;
	Player* player_ = nullptr;
	Beam* beam_ = nullptr;
	Enemy* enemy_ = nullptr;
	GamePlay* gameplay_ = nullptr;
	DebugText* debugText_ = nullptr;
	int gameScore_ = 0;
	int playerLife_ = 3;
};
