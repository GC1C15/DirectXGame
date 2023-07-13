#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Player.h"

class Beam {
public:
	// コンストラクタ
	Beam();
	// デストラクタ
	~Beam();
	// 初期化
	void Initialize(ViewProjection viewProjection, Player* player);
	// 更新
	void Update();
	// 3D描画
	void Draw3D();
	// インプットクラス
	Input* input_ = nullptr;
	void Born();
	void Move();

private:
	ViewProjection viewProjection_;
	// ビーム
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = nullptr;
	WorldTransform worldTransformBeam_[10];
	int BeamTimer_ = 0;
	int BeamFlag_[10];
	Player* player_ = nullptr;
};
