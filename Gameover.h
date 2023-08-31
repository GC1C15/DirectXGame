#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "GamePlay.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "Title.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class GameOver {
public:
	GameOver();
	~GameOver();

	void Start();

	void Initialize();
	int Update();
	void Draw2DNear();

private:
	uint32_t textureHandlegameover_ = 0;
	Sprite* spritegameover_ = nullptr;

	uint32_t textureHandleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;

	Input* input_ = nullptr;

	int timer_ = 0;

	GamePlay* gameplay_ = nullptr;

	Audio* audio_ = nullptr;
	uint32_t soundataHandleGameOverBGM_ = 0;
	uint32_t voiceHandleBGM_ = 0;
};
