#pragma once

#include <vector>
#include <map>
#include <string>

struct AnimationsData {
    std::map<std::string, int> names;
    std::vector<int> num_frames;
    std::vector<float> speeds;
    std::vector<int> offsets;
};