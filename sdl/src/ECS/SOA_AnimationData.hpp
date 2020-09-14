#pragma once

#include <vector>
#include <string>

struct AnimationData {
    std::vector<std::string> current_animations;
    std::vector<float> animation_timers;
    std::vector<int>   animation_indexes;
};