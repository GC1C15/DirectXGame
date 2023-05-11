#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DebugCamera.h>

/// ゲームシーン
/// </summary>
class GameScene {

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

	// プレイヤー更新
	void PlayerUpdate();

	// 敵更新
	void EnemyUpdate();
	// 敵移動
	void EnemyMove();
	// 敵発生
	void EnemyBorn();
	// 敵のフラグ
	int EnemyFlag_ = 0;

	// ビーム更新
	void BeamUpdate();
	// ビーム移動
	void BeamMove();
	// ビーム発生
	void BeamBorn();
	// ビームのフラグ
	int BeamFlag_ = 0;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	DebugCamera* debugCamera_ = nullptr;
	// 背景スプライト
	uint32_t textureHandle_BG = 0;
	Sprite* spriteBG_ = nullptr;
	// ビュープロジェクション(共通)
	ViewProjection viewProjection_;
	// ステージ
	uint32_t textureHandle_Stage = 0;
	Model* model_Stage = nullptr;
	WorldTransform worldTransform_Stage;
	// プレイヤー
	uint32_t textureHandle_Player = 0;
	Model* model_Player = nullptr;
	WorldTransform worldTransform_Player;
	// ビーム
	uint32_t textureHandle_Beam = 0;
	Model* model_Beam = nullptr;
	WorldTransform worldTransform_Beam;
	// 敵
	uint32_t textureHandle_Enemy = 0;
	Model* model_Enemy = nullptr;
	WorldTransform worldTransform_Enemy;
};