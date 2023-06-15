#include "Stage.h"

Stage::Stage() {}

Stage::~Stage() 
{
	//BG
	delete spriteBG_;
	//stage
	delete modelStage_;

}

void Stage::Initialize(ViewProjection viewProjection) 
{
	viewProjection_ = viewProjection;
	//BG
	textureHandleBG_ = TextureManager::Load("bg.jpg");
	spriteBG_ = Sprite::Create(textureHandleBG_, {0, 0});
	//stage
	textureHandleStage_ = TextureManager::Load("stage.jpg");
	modelStage_ = Model::Create();
	worldTransformStage_.Initialize();
	// ステージ位置の変更
	worldTransformStage_.translation_ = {0, -1.5f, 0};
	worldTransformStage_.scale_ = {4.5f, 1, 40};
	// 変更行列の更新
	worldTransformStage_.matWorld_ = MakeAffineMatrix(
	    worldTransformStage_.scale_, worldTransformStage_.rotation_,
	    worldTransformStage_.translation_);
	// 変更行列の定数バッファを転送
	worldTransformStage_.TransferMatrix();
}


void Stage::Update() {}

void Stage::Draw2DFar() { spriteBG_->Draw(); }

void Stage::Draw3D() 
{
	//stage
	modelStage_->Draw(worldTransformStage_, viewProjection_, textureHandleStage_);
}

