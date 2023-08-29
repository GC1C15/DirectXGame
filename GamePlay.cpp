#include "GamePlay.h"

GamePlay::GamePlay() {}

GamePlay::~GamePlay() {
	delete stage_;
	delete player_;
	delete enemy_;
	delete beam_;
}

void GamePlay::Initialize(ViewProjection viewProjection, GamePlay* gameplay) { 
	viewProjection_ = viewProjection;
	gameplay_ = gameplay;
	input_ = Input::GetInstance();
	// stage
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	// BG
	stage_ = new Stage();
	stage_->Initialize(viewProjection_);

	// プレイヤー
	player_ = new Player();
	player_->Initialize(viewProjection_);

	// ビーム
	beam_ = new Beam();
	beam_->Initialize(viewProjection_, player_);

	// エネミー
	enemy_ = new Enemy();
	enemy_->Initialize(viewProjection_, enemy_);

	// デバックテキスト
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();
}

void GamePlay::Update() {
	stage_->Update();
	player_->Update();
	beam_->Update();
	enemy_->Update();
	collision();
}

void GamePlay::Draw3D() {
	stage_->Draw3D();
	player_->Draw3D();
	beam_->Draw3D();
	enemy_->Draw3D();
}

void GamePlay::Draw2DFar() {
	stage_->Draw2DFar();
	debugText_->DrawAll();

	char str[100];
	sprintf_s(str, "SCORE:%d", gameScore_);
	sprintf_s(str, "LIFE:%d", playerLife_);
	debugText_->Print(str, 200, 10, 2);
	debugText_->Print(str, 1000, 10, 2);
}

void GamePlay::Draw2DNear() {}

// 当たり判定関連↓
void GamePlay::collision() {
	collisionPlayerEnemy();
	collisionBeamEnemy();
}

void GamePlay::collisionPlayerEnemy() {
	// 敵が存在すれば
	if (enemy_->GetFlag_() == 1) {
		// 差を求める
		float dx = abs(player_->GetX() - enemy_->GetX());
		float dz = abs(player_->GetZ() - enemy_->GetZ());
		// 衝突したら
		if (dx < 1 && dz < 1) {
			enemy_->Hit();
			playerLife_ -= 1;
		}
	}
}

void GamePlay::collisionBeamEnemy() {
	// 敵が存在すれば
	if (enemy_->GetFlag_() == 1 && beam_->GetFlag_() == 1) {
		// 差を求める
		float bx = abs(enemy_->GetX() - beam_->GetX());
		float bz = abs(enemy_->GetZ() - beam_->GetZ());
		// 衝突したら
		if (bx < 1 && bz < 1) {
			enemy_->Hit();
			beam_->Hit();
			gameScore_ += 100;
		}
	}
}
// 当たり判定関連↑
