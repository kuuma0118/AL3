#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

class Player {
public:
	void Intialize(Model* model, uint32_t texturehandle);

	void Update();

	void Draw(ViewProjection viewProjection_);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};
