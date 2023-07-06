#pragma once

#include "Audio.h"
#include "DebugText.h"
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
	int EnemyFlag_[10] = {};
	// 演出
	void EnemyJump();

	// ビーム更新
	void BeamUpdate();
	// ビーム移動
	void BeamMove();
	// ビーム発生
	void BeamBorn();
	// ビームのフラグ
	int BeamFlag_[10] = {};
	// 衝突判定
	void collision();
	// 敵とプレイヤーの衝突判定
	void collisionPlayerEnemy();
	// ビームと敵の衝突判定
	void collisionBeamEnemy();

	// ゲームプレイ更新
	void GamePlayUpdate();
	// ゲームプレイ3D表示
	void GamePlayDraw3D();
	// ゲームプレイ背景2D表示
	void GamePlayDraw2DBack();
	// ゲームプレイ近景2D表示
	void GamePlayDraw2DNear();
	// タイトル近景2D表示
	void GameTitleDraw2DNear();
	// ゲームオーバー近景2D表示
	void GameGameoverDraw2DNear();
	// タイトル更新
	void TitleUpdate();
	void GameoverUpdate();
	void GameStartUpdate();
	// ステージ更新
	void StageUpdate();
	//スコア数値の表示
	void DrawScore();

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
	WorldTransform worldTransform_Stage[20];
	// プレイヤー
	uint32_t textureHandle_Player = 0;
	Model* model_Player = nullptr;
	WorldTransform worldTransform_Player;
	// ビーム
	uint32_t textureHandle_Beam = 0;
	Model* model_Beam = nullptr;
	WorldTransform worldTransform_Beam[10];
	int BeamTimer_ = 0;
	// 敵
	uint32_t textureHandle_Enemy = 0;
	Model* model_Enemy = nullptr;
	WorldTransform worldTransform_Enemy[10];
	float enemySpeed_[10] = {};
	// テキスト
	DebugText* debugText_ = nullptr;
	int gameScore_ = 0;
	int playerLife_ = 3;
	Sprite* spriteLife_[3] = {};
	Sprite* spriteNumber_[5] = {};
	Sprite* spriteScore_ = nullptr;
	uint32_t textureHandle_Number = 0;
	uint32_t textureHandle_Score = 0;
	// シーン(0:ゲームシーン 1:タイトル)
	int sceneMode_ = 1;
	// タイトル(スプライト)
	uint32_t textureHandle_title = 0;
	uint32_t textureHandle_enter = 0;
	uint32_t textureHandle_gameover = 0;
	Sprite* spriteTitle_ = nullptr;
	Sprite* spriteEnter_ = nullptr;
	Sprite* spriteGameover_ = nullptr;
	int gameTimer_ = 0;
	int charTimer_ = 0;
	// サウンド
	uint32_t soundDataHandleTitleBGM_ = 0;    // タイトルBGM
	uint32_t soundDataHandleGamePlayBGM_ = 0; // ゲームプレイヤーBGM
	uint32_t soundDataHandleGameOverBGM_ = 0; // ゲームオーバーBGM
	uint32_t soundDataHandleHitPlayerSE_ = 0; // プレイヤーヒットSE
	uint32_t soundDataHandleEnemyHitSE_ = 0;  // エネミーヒットSE
	uint32_t voiceHandleBGM_ = 0;             // 音声再生ハンドル
	// 演出
	float enemyJumpSpeed_[10] = {};
	// プレイヤー点滅表示
	int playerTimer_ = 0;
};