#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() { delete modelEnemy_; }

void Enemy::Initialize(ViewProjection viewProjection, Enemy* enemy) {
	viewProjection_ = viewProjection;
	enemy_ = enemy;
	//エネミー
	textureHandleEnemy_ = TextureManager::Load("enemy.png");
	modelEnemy_ = Model::Create();
	worldTransformEnemy_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformEnemy_.Initialize();
}

void Enemy::Update() {
	// 敵の更新
	Move();
	Born();
	Jump();
	worldTransformEnemy_.matWorld_ = MakeAffineMatrix(
	worldTransformEnemy_.scale_, worldTransformEnemy_.rotation_,
	worldTransformEnemy_.translation_);
		// 変更行列を定数バッファに転送
		worldTransformEnemy_.TransferMatrix();
}

void Enemy::Move() {
	if (worldTransformEnemy_.translation_.x < -4) {
		enemySpeed_ *= -1.0f;
	}
	if (worldTransformEnemy_.translation_.x > 4) {
		enemySpeed_ *= -1.0f;
	}

	if (GetFlag_() == 1) {
		worldTransformEnemy_.translation_.x += enemySpeed_;
		worldTransformEnemy_.translation_.z -= gameTimer_ / 1000.0f;
		worldTransformEnemy_.rotation_.x -= 0.1f;
	}
	if (worldTransformEnemy_.translation_.z < -5.0f) {
		worldTransformEnemy_.translation_.z = 40.0f;
		EnemyFlag_ = 0;
		//EnemyFlag_ = enemy_->GetFlag_();
	}
}

void Enemy::Born() {
	if (GetFlag_() == 0) {
		gameTimer_++;
		if (rand() % 10 == 0) {
			int x = rand() % 80;
			float x2 = (float)x / 10 - 4;
			worldTransformEnemy_.translation_.x = x2;
			worldTransformEnemy_.translation_.z = 40.0f;
			EnemyFlag_ = 1;
			//EnemyFlag_ = enemy_->GetFlag_();

			if (rand() % 2 == 0) {
				enemySpeed_ = 0.1f;
			} else {
				enemySpeed_ = -0.1f;
			}
		}
	}
}

void Enemy::Jump() {
	if (GetFlag_() == 2) {
		worldTransformEnemy_.translation_.y += enemyJumpSpeed_;
		enemyJumpSpeed_ -= 0.1f;
		worldTransformEnemy_.translation_.x += enemySpeed_ * 2;
		if (worldTransformEnemy_.translation_.y < -3) {
			EnemyFlag_ = 0;
			//EnemyFlag_ = enemy_->GetFlag_();
			worldTransformEnemy_.translation_.y = 0;
		}
	}
}

void Enemy::Draw3D() {
	if (GetFlag_() != 0) {
		modelEnemy_->Draw(worldTransformEnemy_, viewProjection_, textureHandleEnemy_);
	}
}
