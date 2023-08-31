#include "Gameover.h"

Gameover::Gameover() {}

Gameover::~Gameover() { delete spriteGameover_; }

void Gameover::Initialize() 
{ 
	input_ = Input::GetInstance();
	textureHandle_gameover = TextureManager::Load("gameover.png");
	spriteGameover_ = Sprite::Create(textureHandle_gameover, {0, 0});
	// エンター
	textureHandle_enter = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandle_enter, {400, 360});
}

int Gameover::Update() 
{
	charTimer_++;
	if (input_->TriggerKey(DIK_RETURN)) 
	{
		return 1;
	}
	return 2; 
}

void Gameover::Draw2DNear() {
	spriteGameover_->Draw();
	if (charTimer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}
}
