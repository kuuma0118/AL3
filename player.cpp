#include "player.h"


void Player::Intialize(Model* model, uint32_t texturehandle) { 
	assert(model);

	model_ = model;
	textureHandle_ = texturehandle;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

void Player::Update() { worldTransform_.TransferMatrix(); }

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}
