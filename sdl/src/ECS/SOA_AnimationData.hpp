#pragma once

#include <vector>
#include <string>

struct AnimationData {
    std::vector<std::string> current_animations;
    std::vector<float> timers;
    std::vector<int>   current_frame;
};