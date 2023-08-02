#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "player/PlayerBullet.h"
#include <list>
#include "collider/Collider.h"	
#include "collider/CollisionConfig.h"

class Player : public Collider {
public:
	~Player();

	
	void Initialize(Model* model, uint32_t& textureHandle);
	
	void Update();

	void Draw(ViewProjection& viewProjection);

	void Rotate();

	void Attack();

	void OnCollision() override;

	Vector3 GetWorldPosition() override;

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 自キャラ
	Player* player_ = nullptr;
	// キーボード入力
	Input* input_ = nullptr;
	// リスト
	std::list<PlayerBullet*> bullets_;
};