#include <iostream>
#include <string>
#include <vector>
#include "utils.h"

int main() {
    std::vector<std::string> input_data = InputData(1);
    std::vector<int> depth_measurements;
    for (const auto &input_line : input_data) {
        depth_measurements.emplace_back(std::stoi(input_line));
    }

    int previous_depth = depth_measurements[0];
    int current_depth = 0;
    int depth_increased = 0;

    for(auto i=1; i < depth_measurements.size(); i++) {
        current_depth = depth_measurements[i];
        if (current_depth > previous_depth) {
            depth_increased ++;
        }
        previous_depth = current_depth;
    }

    int previous_depth_window = depth_measurements[0] + depth_measurements[1] + depth_measurements[2];
    int current_depth_window = depth_measurements[0] + depth_measurements[1] + depth_measurements[2];
    int depth_increased_window = 0;

    for(auto i=3; i < depth_measurements.size(); i++) {
        current_depth_window = current_depth_window - depth_measurements[i-3] + depth_measurements[i];
        if (current_depth_window > previous_depth_window) {
            depth_increased_window ++;
        }
        previous_depth_window = current_depth_window;
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day 1 - Part 1: Number of steps with increased depth is <" << depth_increased << ">." << std::endl;
    std::cout << "Day 1 - Part 2: Number of sliding windows with increased depth is <" << depth_increased_window << ">." << std::endl;

    return 0;
}
