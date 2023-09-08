#pragma once
#include "../IEffect.h"

// includeが必要なファイルは可能な限りcppでincludeすること（循環参照防止）

class Player;

// エフェクトの名前をクラス名に
class BlockUpperMove
	: public IEffect {
public:	// メンバ関数
	BlockUpperMove(Model* model, Vector3 position);
	~BlockUpperMove();

	// エフェクトの処理が終わったら必ずisEndをtrueに（変数はIEffect.hで定義済み）
	// Update、Drawは最初にisEndがtrueならばreturnすること

	void Initialize() override;	// 初期化
	void Update() override;	// 更新
	void Draw(const ViewProjection& viewProjection) override;	// 描画

private: // メンバ定数

	/*const float kUpperMoveFrame = 0.0f;*/

	//イージング終了時間
	const float kUpperMoveHeight = 60.0f;
	/*const int kUpperMovetime = 30;*/

	//ブロック消滅時間
	const int blockEndtime = 90;

	//ブロックスタート地点
	const float blockStart = 0.0f;

	//ブロック最終到達地点
	const float blockEnd = 10.0f;

private: // メンバ変数
	
	// ブロックのモデル
	Model* model_ = nullptr;
	// ブロックのワールドトランスフォーム
	WorldTransform transform_;

	// 経過フレーム
	int elapsedFrame_ = 0;

	// テクスチャ
	uint32_t textureNum_;

};