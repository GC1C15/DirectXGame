#include "Player.h"

Player::Player() {}

Player::~Player() { delete modelPlayer_; }

void Player::Initialize(ViewProjection viewProjection) {
	viewProjection_ = viewProjection;
	// プレイヤー
	textureHandlePlayer_ = TextureManager::Load("player.png");
	modelPlayer_ = Model::Create();
	worldTransformPlayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformPlayer_.Initialize();
	// インプットクラス
	input_ = Input::GetInstance();
}

void Player::Update() {
	// 変更行列の更新
	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);
	// 変更行列の定数バッファを転送
	worldTransformPlayer_.TransferMatrix();
	if (input_->PushKey(DIK_RIGHT)) {
		worldTransformPlayer_.translation_.x += 0.1f;
	}
	if (input_->PushKey(DIK_LEFT)) {
		worldTransformPlayer_.translation_.x -= 0.1f;
	}
	if (worldTransformPlayer_.translation_.x > 4) {
		worldTransformPlayer_.translation_.x = 4;
	}
	if (worldTransformPlayer_.translation_.x < -4) {
		worldTransformPlayer_.translation_.x = -4;
	}

}

void Player::Draw3D() {
	// stage
	modelPlayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);
}