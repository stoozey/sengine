#ifndef SENGINE_TIMER_H
#define SENGINE_TIMER_H

#include <functional>

#include "datatypes/clock.h"

class Timer {
public:
    void SetTriggerInterval(int triggerIntervalMilliseconds, std::function<void ()> onTrigger);

    void Tick();
private:
    std::function<void ()> trigger;
    Clock clock;

    int triggerInterval;
    int triggerTimer;
};

#endif //SENGINE_TIMER_H
