#include "Enemy.h"
#include "MT3Math.h"
#include <cassert>

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("1.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void Enemy::Update() {
	(this->*EfuncTable[static_cast<size_t>(phase_)])();

	worldTransform_.UpdateMatrix();

	// switch (phase_) {
	// case Phase::Approach:
	//	Approach();
	//	break;
	//
	// case Phase::Leave:
	//	Leave();
	//	break;
	//
	// default:
	//	break;
	// }
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Approach() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (worldTransform_.translation_.z < -15.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, {-0.5f, 0.5f, 0.0f});
}

void (Enemy::*Enemy::EfuncTable[])() = {&Enemy::Approach, &Enemy::Leave};