#include "Beam.h"

Beam::Beam() {}

Beam::~Beam() { delete modelBeam_; }

void Beam::Initialize(ViewProjection viewProjection) {
	viewProjection_ = viewProjection;
	// �v���C���[
	textureHandleBeam_ = TextureManager::Load("player.png");
	modelBeam_ = Model::Create();
	textureHandleBeam_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformBeam_.Initialize();
	// �C���v�b�g�N���X
	input_ = Input::GetInstance();
}

void Beam::Update() {
	// �ύX�s��̍X�V
	textureHandleBeam_.matWorld_ = MakeAffineMatrix(
	    worldTransformBeam_.scale_, worldTransformBeam_.rotation_,
	    worldTransformBeam_.translation_);
	// �ύX�s��̒萔�o�b�t�@��]��
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
