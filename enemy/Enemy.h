#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "EnemyState.h"
#include "MT3Math.h"
#include "EnemyBullet.h"

class Player;

class EnemyState;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void Move(Vector3 velocity);
	void Fire();
	void ChangingState(EnemyState* newState);

	void OnCollision();

	Vector3 GetPosition() { return worldTransform_.translation_; }
	Vector3 GetSpeed() { return velocity_; }
	void SetPosition(const Vector3& position) { worldTransform_.translation_ = position; }

	static const int kFireInterval = 60;
	int32_t fireTimer;

	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition();

	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }


private:

	EnemyState* phase_ = nullptr;

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;

	std::list<EnemyBullet*> bullets_;

	Player* player_ = nullptr;
};