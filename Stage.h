#pragma once

#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"MathUtilityForText.h"

class Stage {
public:
	// コンストラクタ
	Stage();
	// デストラクタ
	~Stage();

	// 初期化
	void Initialize(ViewProjection viewProjection);
	// 更新
	void Update();
	// 2D背景描画
	void Draw2DFar();
	// 3D描画
	void Draw3D();

private:
	ViewProjection viewProjection_;
	//BG
	uint32_t textureHandleBG_ = 0;
	Sprite* spriteBG_ = nullptr;
	//stage
	uint32_t textureHandleStage_ = 0;
	Model* modelStage_ = nullptr;
	WorldTransform worldTransformStage_;
};
