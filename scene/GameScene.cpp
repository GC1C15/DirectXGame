#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete gameplay_;
	delete title_;
	delete gamaover_;
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
	gamaover_ = new GameOver();

	gameplay_->Initialize(viewProjection_, player_);
	title_->Initialize();
	gamaover_->Initialize();
}

void GameScene::Update() {
	int oldSceneMode = sceneMode_;

	switch (sceneMode_) {
	case 0:
		sceneMode_ = gameplay_->Update();
		gameplay_->Shot();
		break;
	case 1:
		sceneMode_ = title_->Update();
		break;
	case 2:
		sceneMode_ = gamaover_->Update();
		break;
	}

	if (oldSceneMode != sceneMode_) {
		switch (sceneMode_) {
		case 0:
			gameplay_->Sound();
			gameplay_->Start();
			break;
		case 1:
			title_->Start();
			break;
		case 2:
			gamaover_->Start();
			break;
		}
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
	switch (sceneMode_) {
	case 0:
		gameplay_->Draw2DFar();
		break;
	case 2:
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
	switch (sceneMode_) {
	case 0:
		gameplay_->Draw3D();
		break;
	case 2:
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
	switch (sceneMode_) {
	case 0:
		gameplay_->Draw2DNear();
		break;
	case 1:
		title_->Draw2DNear();
		break;
	case 2:
		gameplay_->Draw2DNear();
		gamaover_->Draw2DNear();
		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
