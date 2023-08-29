#pragma once

#include "Audio.h"
#include "Beam.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "Stage.h"
#include "Enemy.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugText.h"
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
	ViewProjection viewProjection_;

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// 衝突判定
	void collision();
	// 敵とプレイヤーの衝突判定
	void collisionPlayerEnemy();
	// ビームと敵の衝突判定
	void collisionBeamEnemy();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Stage* stage_ = nullptr;
	Player* player_ = nullptr;
	Beam* beam_ = nullptr;
	Enemy* enemy_ = nullptr;
	DebugText* debugText_ = nullptr;
	int gameScore_ = 0;
	int playerLife_ = 3;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};