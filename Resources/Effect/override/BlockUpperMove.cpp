#include "BlockUpperMove.h"
#include "Player.h"
#include <assert.h>

#include "../Easing.h"

BlockUpperMove::BlockUpperMove(Model* model, Vector3 position) {
	model_ = model;
	transform_.Initialize();
	transform_.translation_ = position;

	Initialize();
}
BlockUpperMove::~BlockUpperMove() {}

void BlockUpperMove::Initialize() {
	/*float elapsedFrame_ = 0.0f;*/
	textureNum_ = TextureManager::GetInstance()->Load("./Resources/sample.png");
}
void BlockUpperMove::Update() {
	elapsedFrame_++;// 経過フレーム+1
	// 行列更新
	transform_.UpdateMatrix();

	//イージング無し
	//if (elapsedFrame_ < kUpperMovetime) {
	//	transform_.translation_.y = elapsedFrame_ / kUpperMoveHeight;    
	//}
	
	//イージング有り
	transform_.translation_.y = blockStart + (blockEnd - blockStart) * Easing::EaseOutElastic(elapsedFrame_ / kUpperMoveHeight);  
	
	if (elapsedFrame_ > blockEndtime) {
		isEnd = true;
	}
}

void BlockUpperMove::Draw(const ViewProjection& viewProjection) {
	model_->Draw(transform_, viewProjection, textureNum_);
}