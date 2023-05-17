#include "Player.h"

void Player::Intialize(Model* model, uint32_t texturehandle) {
	assert(model);

	input_ = Input::GetInstance();
	model_ = model;
	textureHandle_ = texturehandle;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

void Player::Update() { worldTransform_.TransferMatrix(); 
Vector3 move = {0, 0, 0};

const float kCharacterSpeed = 0.2f;

if (input_->PushKey(DIK_LEFT)) {
	move.x  -= kCharacterSpeed;
} else if (input_->PushKey(DIK_RIGHT)) {
	move.x += kCharacterSpeed;
}
if (input_->PushKey(DIK_UP)) {
	move.y -= kCharacterSpeed;
} else if (input_->PushKey(DIK_DOWN)) {
	move.y += kCharacterSpeed;
}
}



void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}
