#include "Enemy.h"
#include <cassert>
#include "MT3Math.h"
#include "player/Player.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}

	delete phase_;
}

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("1.png");

	phase_ = new EnemyApproach();
	phase_->Initialize(this);

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void Enemy::Update() {
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	phase_->Update();
	worldTransform_.UpdateMatrix();

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::ChangingState(EnemyState* newState) {
	delete phase_;
	phase_ = newState;
	phase_->Initialize(this);
}

void Enemy::Move(Vector3 velocity) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}

void Enemy::Fire() {
	assert(player_);

	const float kBulletSpeed = 1.0f;

	Vector3 playerPosition = player_->GetWorldPosition();
	Vector3 enemyPosition = this->GetWorldPosition();
	Vector3 velocity = Subtract(playerPosition, enemyPosition);
	velocity = Normalize(velocity);

	velocity.x *= kBulletSpeed;
	velocity.y *= kBulletSpeed;
	velocity.z *= kBulletSpeed;

	EnemyBullet* newBullet = new EnemyBullet();

	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	bullets_.push_back(newBullet);
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPosition;
	//worldTransform_.UpdateMatrix();

	worldPosition.x = worldTransform_.matWorld_.m[3][0];
	worldPosition.y = worldTransform_.matWorld_.m[3][1];
	worldPosition.z = worldTransform_.matWorld_.m[3][2];
	return worldPosition;
}