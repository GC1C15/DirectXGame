#include "GamePlay.h"

GamePlay::GamePlay() {}

GamePlay::~GamePlay() {
	delete stage_;
	delete player_;

	for (Beam* beam : beamTable_) {
		delete beam;
	}

	for (Enemy* enemy : enemyTable_) {
		delete enemy;
	}

	for (int i = 0; i < 5; i++) {
		delete spriteNumber_[i];
	}

	for (int i = 0; i < playerLife_; i++) {
		delete spriteLife_[i];
	}

	delete spriteScore_;
}

void GamePlay::Initialize(ViewProjection viewProjection, Player* player) {

	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_ = viewProjection;
	player_ = player;

	stage_ = new Stage();
	player_ = new Player();

	for (int i = 0; i < 10; i++) {
		beamTable_[i] = new Beam();
	}

	for (int i = 0; i < 10; i++) {
		enemyTable_[i] = new Enemy();
	}

	stage_->Initialize(viewProjection_);
	player_->Initialize(viewProjection_);

	for (Beam* beam : beamTable_) {
		beam->Initialize(viewProjection_, player_);
	}

	for (Enemy* enemy : enemyTable_) {
		enemy->Initialize(viewProjection_);
	}

	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();

	soundataHandleEnemySE_ = audio_->LoadWave("Audio/chord.wav");
	soundataHandlePlayerSE_ = audio_->LoadWave("Audio/tada.wav");

	textureHandleNumber_ = TextureManager::Load("number.png");

	textureHandleScore_ = TextureManager::Load("score.png");
	spriteScore_ = Sprite::Create(textureHandleScore_, {170, 0});

	textureHandleNumber_ = TextureManager::Load("number.png");

	textureHandleLife_ = TextureManager::Load("player.png");

	for (int i = 0; i < 5; i++) {
		spriteNumber_[i] = Sprite::Create(textureHandleNumber_, {300.0f + i * 26, 0});
	}

	for (int i = 0; i < playerLife_; i++) {
		spriteLife_[i] = Sprite::Create(textureHandleLife_, {800.0f + i * 60, 10});
		spriteLife_[i]->SetSize({40, 40});
	}
}

void GamePlay::CollisionPlayerEnemy() {
	for (Enemy* enemy : enemyTable_) {

		if (enemy->GetFlag() == 1) {

			float dx = abs(player_->GetX() - enemy->GetX());
			float dz = abs(player_->GetZ() - enemy->GetZ());

			if (dx < 1 && dz < 1) {
				enemy->Hit();
				playerLife_ -= 1;
				playerTimer = 60;
				audio_->PlayWave(soundataHandlePlayerSE_);
			}

			if (playerLife_ <= 0) {
				flag_ = 1;
			}
		}
	}
}

void GamePlay::CollisionBeamEnemy() {
	for (Enemy* enemy : enemyTable_) {
		for (Beam* beam : beamTable_) {
			if (enemy->GetFlag() == 1 && beam->GetFlag() == 1) {
				float dx = abs(beam->GetX() - enemy->GetX());
				float dz = abs(beam->GetZ() - enemy->GetZ());

				if (dx < 1 && dz < 1) {
					enemy->Hit();
					beam->Hit();
					enemy->JumpHit();
					gameScore_ += 1;

					audio_->PlayWave(soundataHandleEnemySE_);
				}
			}
		}
	}
}

int GamePlay::Update() {
	stage_->Update();
	player_->Update();

	gameTimer_++;

	for (Beam* beam : beamTable_) {
		beam->Update();
	}

	for (Enemy* enemy : enemyTable_) {
		enemy->Update(gameTimer_);
	}

	if (playerTimer >= 0) {
		playerTimer--;
	}

	CollisionPlayerEnemy();
	CollisionBeamEnemy();

	if (flag_ == 1) {
		audio_->StopWave(voiceHandleBGM1_);

		return 2;
	}

	return 0;
}

void GamePlay::Start() {
	gameScore_ = 0;
	playerLife_ = 3;

	player_->Start();

	for (Enemy* enemy : enemyTable_) {
		enemy->Start();
	}

	for (Beam* beam : beamTable_) {
		beam->Start();
	}

	flag_ = 0;
	gameTimer_ = 0;

	playerTimer = 0;
}

void GamePlay::Shot() {
	if (shotTimer_ == 0) {

		if (input_->PushKey(DIK_SPACE)) {
			for (Beam* beam : beamTable_) {
				if (beam->GetFlag() == 0) {

					beam->Born();
					beam->Update();

					shotTimer_ = 1;
					break;
				}
			}
		}
	} else {
		shotTimer_++;

		if (shotTimer_ > 10) {
			shotTimer_ = 0;
		}
	}
}

void GamePlay::Sound() {
	audio_ = Audio::GetInstance();
	soundataHandleGamePlayBGM_ = audio_->LoadWave("Audio/Ring08.wav");

	voiceHandleBGM1_ = audio_->PlayWave(soundataHandleGamePlayBGM_, true);
}

void GamePlay::Draw2DFar() { stage_->Draw2DFar(); }

void GamePlay::Draw3D() {
	stage_->Draw3D();

	for (Beam* beam : beamTable_) {
		beam->Draw3D();
	}

	for (Enemy* enemy : enemyTable_) {
		enemy->Draw3D();
	}

	if (playerTimer % 4 < 2) {
		player_->Draw3D();
	}
}

void GamePlay::DrawScore() {
	debugText_->DrawAll();

	int eachNumber[5] = {};
	int number = gameScore_;

	int keta = 10000;

	for (int i = 0; i < 5; i++) {
		eachNumber[i] = number / keta;
		number = number % keta;
		keta = keta / 10;
	}

	for (int i = 0; i < 5; i++) {
		spriteNumber_[i]->SetSize({32, 64});
		spriteNumber_[i]->SetTextureRect({32.0f * eachNumber[i], 0}, {32, 64});
		spriteNumber_[i]->Draw();
	}

	for (int i = 0; i < playerLife_; i++) {
		spriteLife_[i]->Draw();
	}
}

void GamePlay::Draw2DNear() {
	DrawScore();

	spriteScore_->Draw();
}
