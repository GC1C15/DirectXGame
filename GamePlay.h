#pragma once

#include "Audio.h"
#include "Beam.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "Stage.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class GamePlay {
public:
	GamePlay();
	~GamePlay();

	void Initialize(ViewProjection viewProjection, Player* player);
	int Update();
	void Draw2DNear();
	void Draw2DFar();
	void Draw3D();

	void Start();
	void Shot();
	void Sound();
	void DrawScore();

	void CollisionPlayerEnemy();
	void CollisionBeamEnemy();

private:
	ViewProjection viewProjection_;

	Stage* stage_ = nullptr;
	Player* player_ = nullptr;
	Beam* beamTable_[10] = {};
	Enemy* enemyTable_[10] = {};
	DebugText* debugText_ = nullptr;

	int flag_ = 0;

	int gameScore_ = 0;
	int playerLife_ = 3;

	int shotTimer_ = 0;

	int gameTimer_ = 0;

	Input* input_ = nullptr;

	Audio* audio_ = nullptr;

	uint32_t soundataHandleGamePlayBGM_ = 0;
	uint32_t voiceHandleBGM1_ = 0;

	uint32_t soundataHandleEnemySE_ = 0;
	uint32_t soundataHandlePlayerSE_ = 0;

	uint32_t textureHandleNumber_ = 0;
	Sprite* spriteNumber_[5] = {};

	uint32_t textureHandleScore_ = 0;
	Sprite* spriteScore_ = nullptr;

	uint32_t textureHandleLife_ = 0;
	Sprite* spriteLife_[3] = {};

	int playerTimer = 0;
};
