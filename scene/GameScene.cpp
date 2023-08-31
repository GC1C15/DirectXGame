#include "GameScene.h"
#include "TextureManager.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete gameplay_;
	delete title_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();
	gameplay_ = new GamePlay();
	title_ = new Title();
	gameplay_->Initialize(viewProjection_);
	title_->Initialize();
}

void GameScene::Update() {
	switch (sceneMode)
	{ 
		case 0: 
		gameplay_->Update();//ゲームプレイ更新
		break;

		case 1:
		sceneMode = title_->Update(); // タイトル更新
		break;
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	switch (sceneMode) {
	case 0:
		gameplay_->Draw2DFar();
		break;

	}
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
	switch (sceneMode) {
	case 0:
		gameplay_->Draw3D();
		break;
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
	switch (sceneMode) {
	case 0:
		gameplay_->Draw2DNear();
		break;
	case 1:
		title_->Draw2DNear();
		break;

	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}