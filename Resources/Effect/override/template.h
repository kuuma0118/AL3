#pragma once
#include "../IEffect.h"

// includeが必要なファイルは可能な限りcppでincludeすること（循環参照防止）

class Player;

// エフェクトの名前をクラス名に
class EffectName
	: public IEffect {
public:	// メンバ関数
	EffectName(Model* model, const Vector3& position, const Vector3& velocity);
	~EffectName();

	// エフェクトの処理が終わったら必ずisEndをtrueに（変数はIEffect.hで定義済み）
	// Update、Drawは最初にisEndがtrueならばreturnすること

	void Initialize() override;	// 初期化
	void Update() override;	// 更新
	void Draw(const ViewProjection& viewProjection) override;	// 描画

	void Move(Vector3 velocity);

	Vector3 GetPosition() { return worldTransform_.translation_; }
	Vector3 GetSpeed() { return velocity_; }
	void SetPosition(const Vector3& position) { worldTransform_.translation_ = position; }

	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition();
private: // メンバ変数
	// 必要な変数はここで定義
	// 
	Model* model;
	Vector3 velocity;
	Vector3  position_;
	// // 速度
	Vector3 velocity_;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ ;
	//仮
	Player* player_ = nullptr;

	Input* input_ = nullptr;
	// キーボード入力
	EffectName* EffectName_ = nullptr;
};