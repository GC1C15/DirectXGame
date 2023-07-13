#include "Beam.h"
#include"Player.h"
Beam::Beam() {}

Beam::~Beam() { delete modelBeam_; }

void Beam::Initialize(ViewProjection viewProjection, Player* player) {
	viewProjection_ = viewProjection;
	player_ = player;
	// ビーム
	for (int i = 0; i < 10; i++)
	{
	textureHandleBeam_ = TextureManager::Load("beam.png");
	modelBeam_ = Model::Create();
	worldTransformBeam_[i].scale_ = {0.3f, 0.3f, 0.3f};
	worldTransformBeam_[i].Initialize();
	}
	// インプットクラス
	input_ = Input::GetInstance();
}

void Beam::Update() {
	// ビームの更新
	Born();
	Move();
	for (int i = 0; i < 10; i++) {
	worldTransformBeam_[i].matWorld_ = MakeAffineMatrix(
		worldTransformBeam_[i].scale_, worldTransformBeam_[i].rotation_,
		worldTransformBeam_[i].translation_);
	// 変更行列を定数バッファに転送
	worldTransformBeam_[i].TransferMatrix();
	}
}
void Beam::Born() {
	if (BeamTimer_ == 0) {
		for (int i = 0; i < 10; i++) {
			if (input_->PushKey(DIK_SPACE)) {
				if (BeamFlag_[i] == 0) {
					worldTransformBeam_[i].translation_.x = player_->GetX();
					worldTransformBeam_[i].translation_.y = player_->GetY();
					worldTransformBeam_[i].translation_.z = player_->GetZ ();
					BeamTimer_ = 1;
					BeamFlag_[i] = 1;   
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
			worldTransformBeam_[i].translation_.z += 0.5f;
			worldTransformBeam_[i].rotation_.x += 0.1f;
		}

		if (worldTransformBeam_[i].translation_.z > 40.0f) {
			worldTransformBeam_[i].translation_.x = -10.0f;
			worldTransformBeam_[i].translation_.y = -10.0f;
			worldTransformBeam_[i].translation_.z = -10.0f;
			BeamFlag_[i] = 0;
		}
	}
}
// ビーム関連↑

void Beam::Draw3D() {
	// ビーム
	for (int i = 0; i < 10; i++)
	{
		modelBeam_->Draw(worldTransformBeam_[i], viewProjection_, textureHandleBeam_);
	}
}
