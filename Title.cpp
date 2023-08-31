#include "Title.h"

Title::Title() {}

Title::~Title() { delete spriteTitle_; }

void Title::Initialize() {
	textureHandleTitle = TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandleTitle, {0, 0});

	textureHandleEnter = TextureManager::Load("enter.png");
	spriteEnter = Sprite::Create(textureHandleEnter, {400, 500});

	input = Input::GetInstance();

	audio = Audio::GetInstance();
	soundataHandleBGM = audio->LoadWave("Audio/Ring05.wav");

	Start();
}

int Title::Update() {
	timer++;

	if (input->TriggerKey(DIK_RETURN)) {
		audio->StopWave(voiceHandleBGM);
		return 0;
	}

	return 1;
}

void Title::Draw2DNear() {
	spriteTitle_->Draw();

	if (timer % 40 >= 20) {
		spriteEnter->Draw();
	}
}

void Title::Start() { voiceHandleBGM = audio->PlayWave(soundataHandleBGM, true); }