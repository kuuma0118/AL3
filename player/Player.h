#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "player/PlayerBullet.h"
#include <list>
#include "collider/Collider.h"	
#include "collider/CollisionConfig.h"
#include "Sprite.h"

class Player : public Collider {
public:
	~Player();

	
	void Initialize(Model* model, uint32_t& textureHandle, Vector3 position);
	
	void Update(const ViewProjection viewProjection);

	void Draw(ViewProjection& viewProjection);

	void DrawUI();

	void Rotate();

	void Attack();

	void OnCollision() override;

	Vector3 GetWorldPosition() override;

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

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

	WorldTransform worldTransform3DReticle_;
	Sprite* sprite2DReticle_ = nullptr;

	// リスト
	std::list<PlayerBullet*> bullets_;
};