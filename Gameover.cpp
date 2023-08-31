#include "GameOver.h"

GameOver::GameOver() {}

GameOver::~GameOver() { delete spritegameover_; }

void GameOver::Initialize() {
	textureHandlegameover_ = TextureManager::Load("gameover.png");
	spritegameover_ = Sprite::Create(textureHandlegameover_, {0, 200});

	textureHandleEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandleEnter_, {400, 500});

	input_ = Input::GetInstance();
}

int GameOver::Update() {

	timer_++;

	if (input_->TriggerKey(DIK_RETURN)) {
		audio_->StopWave(voiceHandleBGM_);
		return 1;
	}
	return 2;
}

void GameOver::Draw2DNear() {
	spritegameover_->Draw();

	if (timer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}
}

void GameOver::Start() {
	audio_ = Audio::GetInstance();
	soundataHandleGameOverBGM_ = audio_->LoadWave("Audio/Ring09.wav");

	voiceHandleBGM_ = audio_->PlayWave(soundataHandleGameOverBGM_, true);
}
