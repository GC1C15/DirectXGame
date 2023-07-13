#include "Beam.h"

Beam::Beam() {}

Beam::~Beam() { delete modelBeam_; }

void Beam::Initialize(ViewProjection viewProjection) {
	viewProjection_ = viewProjection;
	// �v���C���[
	textureHandleBeam_ = TextureManager::Load("player.png");
	modelBeam_ = Model::Create();
	worldTransformBeam_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformBeam_.Initialize();
	// �C���v�b�g�N���X
	input_ = Input::GetInstance();
}

void Beam::Update() {
	// �ύX�s��̍X�V
	worldTransformBeam_.matWorld_ = MakeAffineMatrix(
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

void Beam::Born() {
	if (BeamTimer_ == 0) {
		for (int i = 0; i < 10; i++) {
			if (input_->PushKey(DIK_SPACE)) {
				if (BeamFlag_[i] == 0) {
					worldTransform_Beam[i].translation_.x = worldTransform_Beam.translation_.x;
					worldTransform_Beam[i].translation_.y = worldTransform_Beam.translation_.y;
					worldTransform_Beam[i].translation_.z = worldTransform_Beam.translation_.z;
					BeamFlag_[i] = 1;
					BeamTimer_ = 1;
					break;
				}
			}
		}
	} else {
		BeamTimer_++;
		if (BeamTimer_ > 10) {
			BeamTimer_ = 0;
		}
	}
}

void Beam::Move() {
	for (int i = 0; i < 10; i++) {
		if (BeamFlag_[i] == 1) {
			worldTransform_Beam[i].translation_.z += 0.5f;
			worldTransform_Beam[i].rotation_.x += 0.1f;
		}

		if (worldTransform_Beam[i].translation_.z > 40.0f) {
			worldTransform_Beam[i].translation_.x = -10.0f;
			worldTransform_Beam[i].translation_.y = -10.0f;
			worldTransform_Beam[i].translation_.z = -10.0f;
			BeamFlag_[i] = 0;
		}
	}
}
// �r�[���֘A��

void Beam::Draw3D() {
	// stage
	modelBeam_->Draw(worldTransformBeam_, viewProjection_, textureHandleBeam_);
}
