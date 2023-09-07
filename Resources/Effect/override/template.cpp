#include "template.h"
#include "Player.h"
#include <assert.h>

EffectName::EffectName(Model* model, const Vector3& position, const Vector3& velocity) {
}
EffectName::~EffectName() {
}

void EffectName::Initialize() {
	// NULL::
	assert(model);
	model_ = model;

	// テクスチャ読み込む
	textureHandle_ = TextureManager::Load("RED.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position_;

	velocity_ = velocity;
}
void EffectName::Update() {
	assert(player_);
	const float EffectNameSpeed = 1.0f;


	Vector3 playerPosition = player_->GetWorldPosition();
	//Vector3 enemyPosition = this->GetWorldPosition();
	Vector3 velocity = Subtract(playerPosition, enemyPosition);
	velocity = Normalize(velocity);

	//velocity.x *= kBulletSpeed;
	velocity.y *= EffectNameSpeed;
	/*velocity.z *= kBulletSpeed;*/
}

void EffectName::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 EffectName::GetWorldPosition() {
	Vector3 worldPosition;
	worldPosition.x = worldTransform_.matWorld_.m[3][0];
	worldPosition.y = worldTransform_.matWorld_.m[3][1];
	worldPosition.z = worldTransform_.matWorld_.m[3][2];
	return worldPosition;
}