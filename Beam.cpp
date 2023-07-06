#include "Beam.h"

Beam::Beam() {}

Beam::~Beam() { delete modelBeam_; }

void Beam::Initialize(ViewProjection viewProjection) {
	viewProjection_ = viewProjection;
	// プレイヤー
	textureHandleBeam_ = TextureManager::Load("player.png");
	modelBeam_ = Model::Create();
	textureHandleBeam_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformBeam_.Initialize();
	// インプットクラス
	input_ = Input::GetInstance();
}

void Beam::Update() {
	// 変更行列の更新
	textureHandleBeam_.matWorld_ = MakeAffineMatrix(
	    worldTransformBeam_.scale_, worldTransformBeam_.rotation_,
	    worldTransformBeam_.translation_);
	// 変更行列の定数バッファを転送
	worldTransformBeam_.TransferMatrix();
	if (worldTransformBeam_.translation_.x > 4) {
		worldTransformBeam_.translation_.x = 4;
	}
	if (worldTransformBeam_.translation_.x < -4) {
		worldTransformBeam_.translation_.x = -4;
	}
}

void Beam::Draw3D() {
	// stage
	modelBeam_->Draw(worldTransformBeam_, viewProjection_, textureHandleBeam_);
}
