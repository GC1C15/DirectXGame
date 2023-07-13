#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player {
public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

	// 初期化
	void Initialize(ViewProjection viewProjection);
	// 更新
	void Update();
	// 3D描画
	void Draw3D();
	// インプットクラス
	Input* input_ = nullptr;
	float GetX() { return worldTransformPlayer_.translation_.x; }
	float GetY() { return worldTransformPlayer_.translation_.y; }
	float GetZ() { return worldTransformPlayer_.translation_.z; }

private:
	ViewProjection viewProjection_;
	// プレイヤー
	uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;
};
