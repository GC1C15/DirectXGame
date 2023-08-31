#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Title {
public:
	Title();
	~Title();

	void Initialize();
	int Update();
	void Draw2DNear();

	void Start();

private:
	uint32_t textureHandleTitle = 0;
	Sprite* spriteTitle_ = nullptr;

	uint32_t textureHandleEnter = 0;
	Sprite* spriteEnter = nullptr;

	Input* input = nullptr;

	int timer = 0;

	Audio* audio = nullptr;
	uint32_t soundataHandleBGM = 0;
	uint32_t voiceHandleBGM = 0;
};