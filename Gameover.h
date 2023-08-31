#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
class Gameover {
public:
	// コンストラクタ
	Gameover();
	// デストラクタ
	~Gameover();
	// 初期化
	void Initialize();
	// 更新
	int Update();
	// 2D前背景描画
	void Draw2DNear();

private:
	Input* input_ = nullptr;
	// タイトル(スプライト)
	uint32_t textureHandle_gameover = 0;
	uint32_t textureHandle_enter = 0;
	Sprite* spriteGameover_ = nullptr;
	Sprite* spriteEnter_ = nullptr;
	int charTimer_ = 0;
	int sceneMode;
};
