#include "enemy/EnemyState.h"

EnemyState::~EnemyState() {

}

EnemyApproach::~EnemyApproach() {
	for (Timer* timeCall : timecalls_) {
		delete timeCall;
	}
}

void EnemyApproach::Update() {
	timecalls_.remove_if([](Timer* timecall) {
		if (timecall->IsFinish()) {
			delete timecall;
			return true;
		}
		return false;
		});
	for (Timer* timecall : timecalls_) {
		timecall->Update();
	}

	const Vector3 kCharacterApproachSpeed = { 0.0f, 0.0f, -0.1f };

	enemy->Move(kCharacterApproachSpeed);
	if (enemy->GetPosition().z <= -15.0f) {
		enemy->ChangingState(new EnemyLeave());
	}
}

void EnemyApproach::Initialize(Enemy* enemy_) {
	enemy = enemy_;
	enemy->fireTimer = enemy->kFireInterval;
	FireAndReset();
}

void EnemyApproach::FireAndReset() {
	enemy->Fire();

	timecalls_.push_back(
		new Timer(std::bind(&EnemyApproach::FireAndReset, this), enemy->kFireInterval));
}

void EnemyLeave::Update() {
	const Vector3 kCharacterLeaveSpeed = { -0.2f, 0.2f, 0.0f };

	enemy->Move(kCharacterLeaveSpeed);
}

void EnemyLeave::Initialize(Enemy* enemy_) { enemy = enemy_; }