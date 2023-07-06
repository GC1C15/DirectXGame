#include "GameScene.h"
#include "TextureManager.h"
#include <MathUtilityForText.h>
#include <cassert>
#include <time.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// 背景のデストラクタ
	delete spriteBG_;
	// ステージのデストラクタ
	delete model_Stage;
	// プレイヤーのデストラクタ
	delete model_Player;
	// ビームのデストラクタ
	delete model_Beam;
	// 敵のデストラクタ
	delete model_Enemy;
	// タイトルのデストラクタ
	delete spriteTitle_;
	delete spriteEnter_;
	delete spriteGameover_;
}

void GameScene::Initialize() {
	srand((unsigned int)time(NULL));
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// 背景(2Dスプライト)
	textureHandle_BG = TextureManager::Load("bg.jpg");
	spriteBG_ = Sprite::Create(textureHandle_BG, {0, 0});

	// ステージ
	textureHandle_Stage = TextureManager::Load("stage2.jpg");
	model_Stage = Model::Create();
	for (int i = 0; i < 20; i++) {
		worldTransform_Stage[i].Initialize();
	}

	// プレイヤー
	textureHandle_Player = TextureManager::Load("player.png");
	model_Player = Model::Create();
	worldTransform_Player.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransform_Player.Initialize();

	// 敵
	textureHandle_Enemy = TextureManager::Load("enemy.png");
	model_Enemy = Model::Create();
	for (int i = 0; i < 10; i++) {
		worldTransform_Enemy[i].scale_ = {0.5f, 0.5f, 0.5f};
		worldTransform_Enemy[i].Initialize();
	}

	// ビーム
	textureHandle_Beam = TextureManager::Load("beam.png");
	model_Beam = Model::Create();
	for (int i = 0; i < 10; i++) {
		worldTransform_Beam[i].scale_ = {0.3f, 0.3f, 0.3f};
		worldTransform_Beam[i].Initialize();
	}

	// デバックテキスト
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();

	//スコア数値,ライフ(2Dスプライト)
	textureHandle_Number = TextureManager::Load("number.png");
	textureHandle_Score = TextureManager::Load("score.png");
	for (int i = 0; i < 5; i++)
	{
		spriteNumber_[i] = Sprite::Create(textureHandle_Number, {300.0f + i * 26, 0});
	}
	spriteScore_ = Sprite::Create(textureHandle_Score, {150.0f, 0});

	// タイトル(2Dスプライト)
	textureHandle_enter = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandle_enter, {400, 360});
	textureHandle_title = TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandle_title, {0, 0});
	textureHandle_gameover = TextureManager::Load("gameover.png");
	spriteGameover_ = Sprite::Create(textureHandle_gameover, {0, 0});

	// サウンドデータの読み込み
	soundDataHandleTitleBGM_ = audio_->LoadWave("Audio/Ring05.wav");
	soundDataHandleGamePlayBGM_ = audio_->LoadWave("Audio/Ring08.wav");
	soundDataHandleGameOverBGM_ = audio_->LoadWave("Audio/Ring09.wav");
	soundDataHandleHitPlayerSE_ = audio_->LoadWave("Audio/chord.wav");
	soundDataHandleEnemyHitSE_ = audio_->LoadWave("Audio/tada.wav");
	// タイトルBGMを再生
	voiceHandleBGM_ = audio_->PlayWave(soundDataHandleTitleBGM_, true);

	// ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();
	// ステージの位置を変更
	for (int i = 0; i < 20; i++) {
		worldTransform_Stage[i].translation_ = {0, -1.5f, 2.0f * i - 5};
		worldTransform_Stage[i].scale_ = {4.5f, 1, 1};
		// 変換行列を更新
		worldTransform_Stage[i].matWorld_ = MakeAffineMatrix(
		    worldTransform_Stage[i].scale_, worldTransform_Stage[i].rotation_,
		    worldTransform_Stage[i].translation_);
		// 変更行列を定数バッファに転送
		worldTransform_Stage[i].TransferMatrix();
	}
}

// プレイヤー関連↓
void GameScene::PlayerUpdate() {
	// プレイヤー更新
	worldTransform_Player.matWorld_ = MakeAffineMatrix(
	    worldTransform_Player.scale_, worldTransform_Player.rotation_,
	    worldTransform_Player.translation_);
	// 変更行列を定数バッファに転送
	worldTransform_Player.TransferMatrix();
	// 移動
	if (input_->PushKey(DIK_RIGHT)) {
		worldTransform_Player.translation_.x += 0.1f;
	}
	if (input_->PushKey(DIK_LEFT)) {
		worldTransform_Player.translation_.x -= 0.1f;
	}
	if (worldTransform_Player.translation_.x > 4) {
		worldTransform_Player.translation_.x = 4;
	}
	if (worldTransform_Player.translation_.x < -4) {
		worldTransform_Player.translation_.x = -4;
	}
	if (playerLife_ <= 0) {
		sceneMode_ = 2;
	}
	if (playerTimer_ > 0) {
		playerTimer_ -= 1;
	}
}
// プレイヤー関連↑

// 敵関連↓
void GameScene::EnemyUpdate() {
	// 敵の更新
	EnemyMove();
	EnemyBorn();
	EnemyJump();
	for (int i = 0; i < 10; i++) {
		worldTransform_Enemy[i].matWorld_ = MakeAffineMatrix(
		    worldTransform_Enemy[i].scale_, worldTransform_Enemy[i].rotation_,
		    worldTransform_Enemy[i].translation_);
		// 変更行列を定数バッファに転送
		worldTransform_Enemy[i].TransferMatrix();
	}
}

void GameScene::EnemyMove() {
	for (int i = 0; i < 10; i++) {
		if (worldTransform_Enemy[i].translation_.x < -4) {
			enemySpeed_[i] *= -1.0f;
		}
		if (worldTransform_Enemy[i].translation_.x > 4) {
			enemySpeed_[i] *= -1.0f;
		}

		if (EnemyFlag_[i] == 1) {
			worldTransform_Enemy[i].translation_.x += enemySpeed_[i];
			//worldTransform_Enemy[i].translation_.z -= 0.1f;
			worldTransform_Enemy[i].translation_.z -= gameTimer_ / 1000.0f;
			worldTransform_Enemy[i].rotation_.x -= 0.1f;
		}
		if (worldTransform_Enemy[i].translation_.z < -5.0f) {
			worldTransform_Enemy[i].translation_.z = 40.0f;
			EnemyFlag_[i] = 0;
		}
	}
}

void GameScene::EnemyBorn() {
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] == 0) {
			gameTimer_++;
			if (rand() % 10 == 0) {
				int x = rand() % 80;
				float x2 = (float)x / 10 - 4;
				worldTransform_Enemy[i].translation_.x = x2;
				worldTransform_Enemy[i].translation_.z = 40.0f;
				EnemyFlag_[i] = 1;

				if (rand() % 2 == 0) {
					enemySpeed_[i] = 0.1f;
				} else {
					enemySpeed_[i] = -0.1f;
				}
			}
			break;
		}
	}
}

void GameScene::EnemyJump() {
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] == 2) {
			worldTransform_Enemy[i].translation_.y += enemyJumpSpeed_[i];
			enemyJumpSpeed_[i] -= 0.1f;
			worldTransform_Enemy[i].translation_.x += enemySpeed_[i] * 2;
			if (worldTransform_Enemy[i].translation_.y < -3) {
				EnemyFlag_[i] = 0;
				worldTransform_Enemy[i].translation_.y = 0;
			}
		}
	}
}
// 敵関連↑

// ビーム関連↓
void GameScene::BeamUpdate() {
	// ビームの更新
	BeamBorn();
	BeamMove();
	for (int i = 0; i < 10; i++) {
		worldTransform_Beam[i].matWorld_ = MakeAffineMatrix(
		    worldTransform_Beam[i].scale_, worldTransform_Beam[i].rotation_,
		    worldTransform_Beam[i].translation_);
		// 変更行列を定数バッファに転送
		worldTransform_Beam[i].TransferMatrix();
	}
}

void GameScene::BeamBorn() {
	if (BeamTimer_ == 0) {
		for (int i = 0; i < 10; i++) {
			if (input_->PushKey(DIK_SPACE)) {
				if (BeamFlag_[i] == 0) {
					worldTransform_Beam[i].translation_.x = worldTransform_Player.translation_.x;
					worldTransform_Beam[i].translation_.y = worldTransform_Player.translation_.y;
					worldTransform_Beam[i].translation_.z = worldTransform_Player.translation_.z;
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

void GameScene::BeamMove() {
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
// ビーム関連↑

// 当たり判定関連↓
void GameScene::collision() {
	collisionPlayerEnemy();
	collisionBeamEnemy();
}

void GameScene::collisionPlayerEnemy() {
	for (int i = 0; i < 10; i++) {
		// 敵が存在すれば
		if (EnemyFlag_[i] == 1) {
			// 差を求める
			float dx =
			    abs(worldTransform_Player.translation_.x - worldTransform_Enemy[i].translation_.x);
			float dz =
			    abs(worldTransform_Player.translation_.z - worldTransform_Enemy[i].translation_.z);
			// 衝突したら
			if (dx < 1 && dz < 1) {
				EnemyFlag_[i] = 0;
				playerLife_ -= 1;
				playerTimer_ = 60;
				// プレイヤーヒットSE
				audio_->PlayWave(soundDataHandleHitPlayerSE_);
			}
		}
	}
}

void GameScene::collisionBeamEnemy() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			// 敵が存在すれば
			if (EnemyFlag_[i] == 1 && BeamFlag_[j] == 1) {
				// 差を求める
				float bx = abs(
				    worldTransform_Enemy[i].translation_.x - worldTransform_Beam[j].translation_.x);
				float bz = abs(
				    worldTransform_Enemy[i].translation_.z - worldTransform_Beam[j].translation_.z);
				// 衝突したら
				if (bx < 1 && bz < 1) {
					EnemyFlag_[i] = 2;
					BeamFlag_[j] = 0;
					gameScore_ += 100;
					enemyJumpSpeed_[i] = 1;
				}
			}
		}
	}
}
// 当たり判定関連↑

void GameScene::Update() {
	switch (sceneMode_) {
	case 0:
		GamePlayUpdate();
		break;
	case 1:
		charTimer_ += 1;
		TitleUpdate();
		GameStartUpdate();
		break;
	case 2:
		charTimer_ += 1;
		GameoverUpdate();
		break;
	}
}

void GameScene::GamePlayUpdate() {
	PlayerUpdate();
	BeamUpdate();
	EnemyUpdate();
	collision();
	GameStartUpdate();
}

void GameScene::StageUpdate() {
	// 各ステージでループ
	for (int i = 0; i < 20; i++) {
		// 手前に移動
		worldTransform_Stage[i].translation_.z -= 0.1f;
		// 端まで来たら奥に戻る
		if (worldTransform_Stage[i].translation_.z < -5) {
			worldTransform_Stage[i].translation_.z += 40;
		}
		// 変更行列を更新
		worldTransform_Stage[i].matWorld_ = MakeAffineMatrix(
		    worldTransform_Stage[i].scale_, worldTransform_Stage[i].rotation_,
		    worldTransform_Stage[i].translation_);
		// 変換行列を定数バッファに転送
		worldTransform_Stage[i].TransferMatrix();
	}
}

void GameScene::GamePlayDraw2DBack() { spriteBG_->Draw(); }

void GameScene::GamePlayDraw3D() {
	for (int i = 0; i < 20; i++) {
		model_Stage->Draw(worldTransform_Stage[i], viewProjection_, textureHandle_Stage);
	}

	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] != 0) {
			model_Enemy->Draw(worldTransform_Enemy[i], viewProjection_, textureHandle_Enemy);
		}
	}
	for (int i = 0; i < 10; i++) {
		if (BeamFlag_[i] == 1) {
			model_Beam->Draw(worldTransform_Beam[i], viewProjection_, textureHandle_Beam);
		}
	}
	if (playerTimer_ % 4 < 2){
		model_Player->Draw(worldTransform_Player, viewProjection_, textureHandle_Player);
	}
}

void GameScene::GamePlayDraw2DNear() {
	for (int i = 0; i < playerLife_; i++) {
		spriteLife_[i] = Sprite::Create(textureHandle_Player, {800.0f + i * 60, 10});
		spriteLife_[i]->SetSize({40, 40});
		spriteLife_[i]->Draw();
	}
}

void GameScene::GameTitleDraw2DNear() {
	// タイトル表示
	spriteTitle_->Draw();
	// エンター表示
	if (charTimer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}
}

void GameScene::GameGameoverDraw2DNear() {
	spriteGameover_->Draw();
	if (charTimer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}
}

void GameScene::TitleUpdate() {
	gameTimer_ = 0;
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneMode_ = 0;
		for (int i = 0; i < 10; i++) {
			EnemyFlag_[i] = 0;
		}
		// BGM切り替え
		audio_->StopWave(voiceHandleBGM_); // 現在のBGMを停止
		voiceHandleBGM_ =
		    audio_->PlayWave(soundDataHandleGamePlayBGM_, true); // ゲームプレイBGM再生
	}
}

void GameScene::GameoverUpdate() {
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneMode_ = 1;
		audio_->StopWave(voiceHandleBGM_);                                  // 現在のBGMを停止
		voiceHandleBGM_ = audio_->PlayWave(soundDataHandleTitleBGM_, true); // ゲームプレイBGM再生
	}
}

void GameScene::GameStartUpdate() {

	for (int i = 0; i < 10; i++) {
		if (sceneMode_ == 2) {
			playerLife_ = 3;
			gameScore_ = 0;
			playerTimer_ = 0;
			worldTransform_Player.translation_.x = 0.0f;
			worldTransform_Enemy[i].translation_.z = 40.0f;
			BeamFlag_[i] = 0;
		}
	}
}

void GameScene::DrawScore() {
	// 各桁の値を取り出す
	int eachNumber[5] = {};
	int number = gameScore_;
	int keta = 10000;
	for (int i = 0; i < 5; i++) {
		eachNumber[i] = number / keta;
		number = number % keta;
		keta = keta / 10;
	}
	// 各桁の数値を表示
	for (int i = 0; i < 5; i++) {
		spriteNumber_[i]->SetSize({32, 64});
		spriteNumber_[i]->SetTextureRect({32.0f * eachNumber[i], 0}, {32, 64});
		spriteNumber_[i]->Draw();
	}
	spriteScore_->Draw();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	// 背景
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	switch (sceneMode_) {
	case 0:
		GamePlayDraw2DBack();
		break;
	case 2:
		GamePlayDraw2DBack();
		break;
	}
	// ↓これは最後に書く,動かさない
	debugText_->DrawAll();

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
	switch (sceneMode_) {
	case 0:
		GamePlayDraw3D();
		break;
	case 2:
		GamePlayDraw3D();
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	switch (sceneMode_) {
	case 0:
		DrawScore();
		GamePlayDraw2DNear();
		break;
	case 1:
		GameTitleDraw2DNear();
		break;
	case 2:
		GameGameoverDraw2DNear();
		break;
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}