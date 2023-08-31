#pragma once
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
	// コンストラクタ
	Title();
	// デストラクタ
	~Title();
	// 初期化
	void Initialize();
	// 更新
	int Update();
	// 2D前背景描画
	void Draw2DNear();

private:
	Input* input_ = nullptr;
	// タイトル(スプライト)
	uint32_t textureHandle_title = 0;
	uint32_t textureHandle_enter = 0;
	Sprite* spriteTitle_ = nullptr;
	Sprite* spriteEnter_ = nullptr;
	int gameTimer_ = 0;
	int charTimer_ = 0;
	int sceneMode;
};
