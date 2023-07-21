#include "timer.h"

Timer::Timer(std::function<void()> callBack, uint32_t time) {
	this->callback_ = callBack;
	this->time_ = time;
}

void Timer::Update() {
	if (isFinish) {
		return;
	}

	time_--;

	if (time_ <= 0) {
		isFinish = true;
		callback_();
	}
}