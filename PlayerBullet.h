#pragma once
#include "MT3Math.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"

class PlayerBullet {
public:
	/// 初期化
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};