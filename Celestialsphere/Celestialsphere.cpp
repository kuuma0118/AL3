#include "Celestialsphere.h"
#include <cassert>

void Celestialsphere::Initialize(Model* model) {
	assert(model);
	model_ = model;
	
	worldTransform_.Initialize();
	worldTransform_.scale_ = {100.0f, 100.0f, 100.0f};
	worldTransform_.UpdateMatrix();
}

void Celestialsphere::Update() {}

void Celestialsphere::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}