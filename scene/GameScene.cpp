#include "scene/GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene()
{
	delete model_;
	delete player_;
	delete enemy_;
	delete debugCamera_;

	delete collisionManager_;
	delete Celestialsphere_;
	delete CelestialModel_;
	delete railCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("sample.png");
	// 3Dモデルの生成
	model_ = Model::Create();
	CelestialModel_ = Model::CreateFromOBJ("skydome", true);
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = new Player();
	Vector3 playerPosition(0, 0, 60);
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_, playerPosition);

	// 敵の生成
	enemy_ = new Enemy;
	// 敵の初期化
	//Vector3 position = {0, 0, 20};
	enemy_->SetPlayer(player_);
	enemy_->Initialize(model_, { 15, 0, 80 }, { 0, 0, -0.1f });

	collisionManager_ = new CollisionManager();
	Celestialsphere_ = new Celestialsphere;
	Celestialsphere_->Initialize(CelestialModel_);
	railCamera_ = new RailCamera;
	railCamera_->Initialize({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });

	player_->SetParent(&railCamera_->GetWorldTransform());


	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update()
{
	player_->Update();

	enemy_->Update();

	collisionManager_->ClearColliders();
	collisionManager_->AddCollider(player_);
	collisionManager_->AddCollider(enemy_);

	for (PlayerBullet* playerBullet : player_->GetBullets()) {
		collisionManager_->AddCollider(playerBullet);
	}

	for (EnemyBullet* enemyBullet : enemy_->GetBullets()) {
		collisionManager_->AddCollider(enemyBullet);
	}

	collisionManager_->CheckAllCollision();

	Celestialsphere_->Update();
	// デバッグカメラのifdef
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;
	}
	else if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}
	// カメラの処理
	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	}
	else {
		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}
#endif
}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	Celestialsphere_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}