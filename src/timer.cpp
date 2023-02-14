#include "timer.h"

void Timer::SetTriggerInterval(int triggerIntervalMilliseconds, std::function<void()> onTrigger) {
    triggerInterval = (triggerIntervalMilliseconds * 10000);
    trigger = onTrigger;
}

void Timer::Tick() {
    triggerTimer += clock.Tick();
    if (triggerTimer < triggerInterval) return;

    triggerTimer = 0;
    trigger();
}