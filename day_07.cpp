#include <iostream>
#include <string>
#include "utils.h"
#include <algorithm>

int FuelCost(int destination, int position) {
    if (destination - position < 0) {
        return position - destination;
    }
    return destination - position;
}

int CrabFuelCost(int destination, int position) {
    int distance = destination - position;
    if (distance < 0) {
        distance = -distance;
    }
    return (distance)*(1+distance)/2;
}

int main() {

    int challenge_id = 7;
    auto input_data = InputData(challenge_id);

    std::stringstream input_stream(input_data[0]);
    std::string next_crab_position;
    std::vector<int> crab_positions;
    while(std::getline(input_stream, next_crab_position, ',')) {
        crab_positions.emplace_back(std::stoi(next_crab_position));
    }
    int left = crab_positions[std::distance(crab_positions.begin(), std::min_element(crab_positions.begin(), crab_positions.end()))];
    int right = crab_positions[std::distance(crab_positions.begin(), std::max_element(crab_positions.begin(), crab_positions.end()))];


    int min_fuel_cost = INT_MAX;
    int min_crab_fuel_cost = INT_MAX;
    for (int current_position=left; current_position<right+1; current_position++) {
        int total_fuel_cost = 0;
        int total_crab_fuel_cost = 0;
        for (auto crab_position : crab_positions) {
            total_fuel_cost += FuelCost(current_position, crab_position);
            total_crab_fuel_cost += CrabFuelCost(current_position, crab_position);
        }
        if (total_fuel_cost < min_fuel_cost) {
            min_fuel_cost = total_fuel_cost;
        }
        if (total_crab_fuel_cost < min_crab_fuel_cost) {
            min_crab_fuel_cost = total_crab_fuel_cost;
        }
    }

    std::cout << "\n* Results *" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << min_fuel_cost << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << min_crab_fuel_cost << std::endl;

    return 0;
}