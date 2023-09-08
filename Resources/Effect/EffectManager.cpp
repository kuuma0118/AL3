#include "EffectManager.h"

// 初期化
// effectsをクリア
void EffectManager::Initialize() {
	effects.clear();
}
// 更新
// 全てのeffectsを更新する
// 更新後にremove_ifで不要な要素を削除
void EffectManager::Update() {
	for (IEffect* effect : effects) {
		effect->Update();
	}

	// 終了したエフェクトを終了させる
	effects.remove_if([](IEffect* effect){
		if (effect->GetIsEnd()) {
			//delete effect;
			return true;
		}
		return false;
	});

}
// 描画
// 全てのeffectsを描画する
void EffectManager::Draw(const ViewProjection& viewProjection) {
	for (IEffect* effect : effects) {
		effect->Draw(viewProjection);
	}
}