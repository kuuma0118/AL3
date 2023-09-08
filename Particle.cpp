#include "Particle.h"
#include "Player.h"
#include <assert.h>

Particle::Particle(Model* model, Vector3 position) {
	model_ = model;
	transform_.Initialize();
	transform_.translation_ = position;

	Initialize();
}
Particle::~Particle() {}

void Particle::Initialize() {
	/*float elapsedFrame_ = 0.0f;*/
	textureNum_ = TextureManager::GetInstance()->Load("./Resources/RED.png");
}
void Particle::Update() {
	elapsedFrame_++;// �o�߃t���[��+1
	// �s��X�V
	transform_.UpdateMatrix();

	//�C�[�W���O����
	//if (elapsedFrame_ < kUpperMovetime) {
	//	transform_.translation_.y = elapsedFrame_ / kUpperMoveHeight;    
	//}


	if (elapsedFrame_ > blockEndtime) {
		isEnd = true;
	}
}

void Particle::Draw(const ViewProjection& viewProjection) {
	for (int num = 0; num < ParticlCount; num++) {
		model_->Draw(transform_, viewProjection, textureNum_);
}