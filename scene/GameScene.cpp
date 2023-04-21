#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<MathUtilityForText.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// 背景のデストラクタ
	delete spriteBG_;
	//ステージのデストラクタ
	delete model_Stage;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//背景(2Dスプライト)
	textureHandle_BG = TextureManager::Load("bg.jpg");
	spriteBG_ = Sprite::Create(textureHandle_BG, {0, 0});
	//ステージ
	textureHandle_Stage = TextureManager::Load("stage.jpg");
	model_Stage = Model::Create();
	worldTransform_Stage.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();
	//ステージの位置を変更
	worldTransform_Stage.translation_ = {0, -1.5f, 0};
	worldTransform_Stage.scale_ = {4.5f, 1, 40};
	//変換行列を更新
	worldTransform_Stage.matWorld_ = MakeAffineMatrix(
	    worldTransform_Stage.scale_,
		worldTransform_Stage.rotation_,
	    worldTransform_Stage.translation_);
	//変更行列を定数バッファに転送
	worldTransform_Stage.TransferMatrix();
}

void GameScene::Update() {}

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
