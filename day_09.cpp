#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "utils.h"

std::vector<std::vector<int>> depth_map;
std::map<std::tuple<int,int>, bool> backtracking;

int DiscoverBasin(int row, int column) {
    if (depth_map[row][column] == 9) {
        return 0;
    }
    if (backtracking.contains(std::tuple(row,column))) {
        return 0;
    }
    backtracking[std::tuple(row,column)] = true;
    return DiscoverBasin(row-1, column) + DiscoverBasin(row+1, column) + DiscoverBasin(row, column-1) + DiscoverBasin(row, column+1) + 1;
}

int main() {

    int challenge_id = 9;
    auto input_data = InputData(challenge_id);

    std::vector<int> padding_line(input_data[0].size()+2, 9);
    depth_map.emplace_back(padding_line);
    for(auto & input_line : input_data) {
        std::vector<int> line = {9};
        for (auto number : input_line) {
            line.emplace_back((int)number - '0');
        }
        line.emplace_back(9);
        depth_map.emplace_back(line);
    }
    depth_map.emplace_back(padding_line);

    std::vector<int> basin_sizes;
    int sum_risk_score = 0;
    for (int row_idx=1; row_idx < depth_map.size() - 1; row_idx++) {
        for (int column_idx=1; column_idx < depth_map[row_idx].size() - 1; column_idx++) {
            int center = depth_map[row_idx][column_idx];
            int left = depth_map[row_idx][column_idx - 1];
            int right = depth_map[row_idx][column_idx + 1];
            int top = depth_map[row_idx - 1][column_idx];
            int bottom = depth_map[row_idx + 1][column_idx];
            if (center<top && center<left && center<right && center<bottom) {
                sum_risk_score += center + 1;
                basin_sizes.emplace_back(DiscoverBasin(row_idx, column_idx));
                backtracking.clear();
            }
        }
    }

    std::sort(basin_sizes.begin(), basin_sizes.end());
    int result = basin_sizes[basin_sizes.size()-1] * basin_sizes[basin_sizes.size()-2] * basin_sizes[basin_sizes.size()-3];

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << sum_risk_score << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << result << std::endl;

    return 0;
}
