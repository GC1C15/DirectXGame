#include "GameScene.h"
#include "TextureManager.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete stage_;
	delete player_;
	delete beam_;
	delete enemy_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

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

	//エネミー
	enemy_ = new Enemy();
	enemy_->Initialize(viewProjection_, enemy_);

	//デバックテキスト
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();
}

// 当たり判定関連↑
void GameScene::Update() {
	stage_->Update();
	player_->Update();
	beam_->Update();
	enemy_->Update();
	collision();
}

// 当たり判定関連↓
void GameScene::collision() {
	collisionPlayerEnemy();
	collisionBeamEnemy();
}

void GameScene::collisionPlayerEnemy() {
	// 敵が存在すれば
	if (enemy_->GetFlag_() == 1) {
		// 差を求める
		float dx = abs(player_->GetX() - enemy_->GetX());
		float dz = abs(player_->GetZ() - enemy_->GetZ());
		// 衝突したら
		if (dx < 1 && dz < 1) 
		{
			enemy_->Hit();
			playerLife_ -= 1;
		}
	}
}

void GameScene::collisionBeamEnemy() {
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


void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	stage_->Draw2DFar();
	//debugText_->Print("AAA", 10, 10, 2);
	debugText_->DrawAll();

	char str[100];
	char str1[100];
	sprintf_s(str, "SCORE:%d", gameScore_);
	sprintf_s(str1, "LIFE:%d", playerLife_);
	debugText_->Print(str, 200, 10, 2);
	debugText_->Print(str1, 1000, 10, 2);
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	stage_->Draw3D();
	player_->Draw3D();
	beam_->Draw3D();
	enemy_->Draw3D();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}