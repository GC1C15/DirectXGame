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
	textureHandle_Stage = TextureManager::Load("stage.jpg");
	model_Stage = Model::Create();
	worldTransform_Stage.Initialize();

	// プレイヤー
	textureHandle_Player = TextureManager::Load("player.png");
	model_Player = Model::Create();
	worldTransform_Player.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransform_Player.Initialize();

	// 敵
	textureHandle_Enemy = TextureManager::Load("enemy.png");
	model_Enemy = Model::Create();
	worldTransform_Enemy.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransform_Enemy.Initialize();

	// ビーム
	textureHandle_Beam = TextureManager::Load("beam.png");
	model_Beam = Model::Create();
	worldTransform_Beam.scale_ = {0.3f, 0.3f, 0.3f};
	worldTransform_Beam.Initialize();

	// ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();
	// ステージの位置を変更
	worldTransform_Stage.translation_ = {0, -1.5f, 0};
	worldTransform_Stage.scale_ = {4.5f, 1, 40};
	// 変換行列を更新
	worldTransform_Stage.matWorld_ = MakeAffineMatrix(
	    worldTransform_Stage.scale_, worldTransform_Stage.rotation_,
	    worldTransform_Stage.translation_);

	// 変更行列を定数バッファに転送
	worldTransform_Stage.TransferMatrix();
}

// プレイヤー関連
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
}
// 敵関連↓

void GameScene::EnemyUpdate() {
	// 敵の更新
	EnemyMove();
	EnemyBorn();
	worldTransform_Enemy.matWorld_ = MakeAffineMatrix(
	    worldTransform_Enemy.scale_, worldTransform_Enemy.rotation_,
	    worldTransform_Enemy.translation_);
	// 変更行列を定数バッファに転送
	worldTransform_Enemy.TransferMatrix();
}

void GameScene::EnemyMove() {
	if (EnemyFlag_ == 1) {
		worldTransform_Enemy.translation_.z -= 0.1f;
		worldTransform_Enemy.rotation_.x -= 0.1f;
	}
	if (worldTransform_Enemy.translation_.z < -5.0f) {
		worldTransform_Enemy.translation_.z = 40.0f;
		EnemyFlag_ = 0;
	}
}

void GameScene::EnemyBorn() {
	if (EnemyFlag_ == 0) {
		int x = rand() % 80;
		float x2 = (float)x / 10 - 4;
		worldTransform_Enemy.translation_.x = x2;
		worldTransform_Enemy.translation_.z = 40.0f;
		EnemyFlag_ = 1;
	}
}

// 敵関連↑

// ビーム関連↓
void GameScene::BeamUpdate() {
	// ビームの更新
	BeamBorn();
	BeamMove();
	worldTransform_Beam.matWorld_ = MakeAffineMatrix(
	    worldTransform_Beam.scale_, worldTransform_Beam.rotation_,
	    worldTransform_Beam.translation_);
	// 変更行列を定数バッファに転送
	worldTransform_Beam.TransferMatrix();
}

void GameScene::BeamBorn() {
	if (input_->PushKey(DIK_SPACE) && BeamFlag_ == 0) {
		worldTransform_Beam.translation_.x = worldTransform_Player.translation_.x;
		worldTransform_Beam.translation_.y = worldTransform_Player.translation_.y;
		worldTransform_Beam.translation_.z = worldTransform_Player.translation_.z;
		BeamFlag_ = 1;
	}
}

void GameScene::BeamMove() {
	if (BeamFlag_ == 1) {
		worldTransform_Beam.translation_.z += 0.1f;
		worldTransform_Beam.rotation_.x += 0.1f;
	}
	if (worldTransform_Beam.translation_.z > 40.0f) {
		worldTransform_Beam.translation_.x = -10.0f;
		worldTransform_Beam.translation_.y = -10.0f;
		worldTransform_Beam.translation_.z = -10.0f;
		BeamFlag_ = 0;
	}
}
// ビーム関連↑

void GameScene::Update() {
	PlayerUpdate();
	BeamUpdate();
	EnemyUpdate();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	// 背景
	spriteBG_->Draw();
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
	// ステージ
	model_Stage->Draw(worldTransform_Stage, viewProjection_, textureHandle_Stage);
	model_Player->Draw(worldTransform_Player, viewProjection_, textureHandle_Player);
	if (EnemyFlag_ == 1) {
		model_Enemy->Draw(worldTransform_Enemy, viewProjection_, textureHandle_Enemy);
	}
	if (BeamFlag_ == 1) {
		model_Beam->Draw(worldTransform_Beam, viewProjection_, textureHandle_Beam);
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

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
