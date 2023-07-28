#include "Beam.h"
#include "Player.h"
Beam::Beam() {}

Beam::~Beam() { delete modelBeam_; }

void Beam::Initialize(ViewProjection viewProjection, Player* player) {
	viewProjection_ = viewProjection;
	player_ = player;
	// ビーム
		textureHandleBeam_ = TextureManager::Load("beam.png");
		modelBeam_ = Model::Create();
		worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
		worldTransformBeam_.Initialize();
	// インプットクラス
	input_ = Input::GetInstance();
}

void Beam::Update() {
	// ビームの更新
	Born();
	Move();
		worldTransformBeam_.matWorld_ = MakeAffineMatrix(
		worldTransformBeam_.scale_, worldTransformBeam_.rotation_,
		worldTransformBeam_.translation_);
		// 変更行列を定数バッファに転送
		worldTransformBeam_.TransferMatrix();
}
void Beam::Born() {
	if (BeamTimer_ == 0) {
		if (input_->PushKey(DIK_SPACE)) {
			if (BeamFlag_ == 0) {
				worldTransformBeam_.translation_.x = player_->GetX();
				worldTransformBeam_.translation_.y = player_->GetY();
				worldTransformBeam_.translation_.z = player_->GetZ();
				BeamTimer_ = 1;
				BeamFlag_ = 1;
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
	if (BeamFlag_ == 1) {
		worldTransformBeam_.translation_.z += 0.5f;
		worldTransformBeam_.rotation_.x += 0.1f;
	}

	if (worldTransformBeam_.translation_.z > 40.0f) {
		worldTransformBeam_.translation_.x = -10.0f;
		worldTransformBeam_.translation_.y = -10.0f;
		worldTransformBeam_.translation_.z = -10.0f;
		BeamFlag_ = 0;
	}
}
// ビーム関連↑

void Beam::Draw3D() {
	// ビーム
	if (BeamFlag_ == 1) 
	{
		modelBeam_->Draw(worldTransformBeam_, viewProjection_, textureHandleBeam_);
	}
}