#include "Title.h"

Title::Title() {}

Title::~Title() { delete spriteTitle_; }

void Title::Initialize() { 
	input_ = Input::GetInstance();
	//タイトル
	textureHandle_title = TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandle_title, {0, 0});
	//エンター
	textureHandle_enter = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandle_enter, {400, 360});
}

int Title::Update() { 
	gameTimer_ = 0;
	charTimer_++;
	if (input_->TriggerKey(DIK_RETURN)) 
	{
		sceneMode = 1;
		return 0;
	}
	return 1;
}

void Title::Draw2DNear() 
{
	// タイトル表示
	spriteTitle_->Draw();
	// エンター表示
	if (charTimer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}
}


