#include "template.h"


void Player::Update() {
	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0, 0, 0};

	// �s��X�V
	worldTransform_.TransferMatrix();

	// �L�����N�^�[�̈ړ����x
	const float kCharacterSpeed = 0.2f;
	// �ړ����E���W
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	float imputFloat3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	// �x�N�^�[�̉��Z
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	// �A�t�B���ϊ��s��̍쐬
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