#pragma once

#include "Audio.h"
#include "Beam.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "GameOver.h"
#include "GamePlay.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "Stage.h"
#include "TextureManager.h"
#include "Title.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

/// <summary>
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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	ViewProjection viewProjection_;

	GamePlay* gameplay_ = nullptr;
	Title* title_ = nullptr;
	GameOver* gamaover_ = nullptr;
	Player* player_ = nullptr;

	int sceneMode_ = 1;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
