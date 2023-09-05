#include "template.h"


void Player::Update() {
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// 行列更新
	worldTransform_.TransferMatrix();

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;
	// 移動限界座標
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	float imputFloat3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	// ベクターの加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	Player::Attack();

	if (bullet_) {
		bullet_->Update();
	}
}

void Player::Draw(ViewProjection& viewProjection_) {
	if (bullet_) {
		bullet_->Draw(viewProjection_);
	}
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}