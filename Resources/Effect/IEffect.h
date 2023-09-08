#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "MT3Math.h"

class IEffect {
public:	// 純粋仮想関数
	virtual ~IEffect() = default;

	virtual void Initialize() = 0;	// 初期化
	virtual void Update() = 0;	// 更新
	virtual void Draw(const ViewProjection& viewProjection) = 0;	// 描画

	// 終了したかを受け取る関数
	bool GetIsEnd() { return isEnd; }

protected:
	bool isEnd = false;	// エフェクトが終了したかどうか
};