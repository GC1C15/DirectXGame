#include "Beam.h"

Beam::Beam() {}

Beam::~Beam() { delete modelBeam_; }

void Beam::Initialize(ViewProjection viewProjection, Player* player) {
	viewProjection_ = viewProjection;
	player_ = player;

	textureHandleBeam_ = TextureManager::Load("beam.png");
	modelBeam_ = Model::Create();
	worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
	worldTransformBeam_.Initialize();

	input_ = Input::GetInstance();
}

void Beam::Update() {
	Move();

	worldTransformBeam_.matWorld_ = MakeAffineMatrix(
	    worldTransformBeam_.scale_, worldTransformBeam_.rotation_,
	    worldTransformBeam_.translation_);
	worldTransformBeam_.TransferMatrix();
}
void Beam::Move() {
	if (aliveFlag_ == 1) {
		worldTransformBeam_.rotation_.x += 0.1f;
		worldTransformBeam_.translation_.z += 0.3f;

		if (worldTransformBeam_.translation_.z >= 40.0f) {
			aliveFlag_ = 0;
		}
	}
}

void Beam::Born() {
	if (input_->TriggerKey(DIK_SPACE) && aliveFlag_ == 0) {
		worldTransformBeam_.translation_.x = player_->GetX();
		worldTransformBeam_.translation_.z = player_->GetZ();

		aliveFlag_ = 1;
	}
}

void Beam::Start() {
	aliveFlag_ = 0;
	worldTransformBeam_.translation_.x = player_->GetX();
	worldTransformBeam_.translation_.z = player_->GetZ();
}

void Beam::Draw3D() {
	if (aliveFlag_ == 1) {
		modelBeam_->Draw(worldTransformBeam_, viewProjection_, textureHandleBeam_);
	}
}
