#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() { delete modelEnemy_; }

void Enemy::Initialize(ViewProjection viewProjection) {
	for (int i = 0; i < 10; i++) {
		viewProjection_ = viewProjection;
		textureHandleEnemy_ = TextureManager::Load("enemy.png");
		modelEnemy_ = Model::Create();
		worldTransformEnemy_[i].scale_ = {0.5f, 0.5f, 0.5f};
		worldTransformEnemy_[i].Initialize();
	}
}

void Enemy::Update() {
	// 敵の更新
	Move();
	Born();
	Jump();
	for (int i = 0; i < 10; i++) {
		worldTransformEnemy_[i].matWorld_ = MakeAffineMatrix(
		    worldTransformEnemy_[i].scale_, worldTransformEnemy_[i].rotation_,
		    worldTransformEnemy_[i].translation_);
		// 変更行列を定数バッファに転送
		worldTransformEnemy_[i].TransferMatrix();
	}
}

void Enemy::Move() {
	for (int i = 0; i < 10; i++) {
		if (worldTransformEnemy_[i].translation_.x < -4) {
			enemySpeed_[i] *= -1.0f;
		}
		if (worldTransformEnemy_[i].translation_.x > 4) {
			enemySpeed_[i] *= -1.0f;
		}

		if (EnemyFlag_[i] == 1) {
			worldTransformEnemy_[i].translation_.x += enemySpeed_[i];
			worldTransformEnemy_[i].translation_.z -= gameTimer_ / 1000.0f;
			worldTransformEnemy_[i].rotation_.x -= 0.1f;
		}
		if (worldTransformEnemy_[i].translation_.z < -5.0f) {
			worldTransformEnemy_[i].translation_.z = 40.0f;
			EnemyFlag_[i] = 0;
		}
	}
}

void Enemy::Born() {
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] == 0) {
			gameTimer_++;
			if (rand() % 10 == 0) {
				int x = rand() % 80;
				float x2 = (float)x / 10 - 4;
				worldTransformEnemy_[i].translation_.x = x2;
				worldTransformEnemy_[i].translation_.z = 40.0f;
				EnemyFlag_[i] = 1;

				if (rand() % 2 == 0) {
					enemySpeed_[i] = 0.1f;
				} else {
					enemySpeed_[i] = -0.1f;
				}
			}
			break;
		}
	}
}

void Enemy::Jump() {
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] == 2) {
			worldTransformEnemy_[i].translation_.y += enemyJumpSpeed_[i];
			enemyJumpSpeed_[i] -= 0.1f;
			worldTransformEnemy_[i].translation_.x += enemySpeed_[i] * 2;
			if (worldTransformEnemy_[i].translation_.y < -3) {
				EnemyFlag_[i] = 0;
				worldTransformEnemy_[i].translation_.y = 0;
			}
		}
	}
}

void Enemy::Draw3D() {
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] != 0) {
			modelEnemy_->Draw(worldTransformEnemy_[i], viewProjection_, textureHandleEnemy_);
		}
	}
}
