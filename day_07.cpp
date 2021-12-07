#include <iostream>
#include <string>
#include "utils.h"
#include <algorithm>
#include <chrono>

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

    auto start = std::chrono::steady_clock::now();

    int challenge_id = 7;
    auto input_data = InputData(challenge_id);

    std::stringstream input_stream(input_data[0]);
    std::string next_crab_position;
    std::vector<int> crab_positions;
    double mean = 0;
    while(std::getline(input_stream, next_crab_position, ',')) {
        int crab_position = std::stoi(next_crab_position);
        mean += crab_position;
        crab_positions.emplace_back(crab_position);
    }
    mean /= crab_positions.size();
    std::sort(crab_positions.begin(), crab_positions.end());
    int median = crab_positions[crab_positions.size()/2];


    int total_fuel_cost = 0;
    int total_crab_fuel_cost = 0;
    for (auto crab_position : crab_positions) {
        total_fuel_cost += FuelCost(median, crab_position);
        total_crab_fuel_cost += CrabFuelCost(int(mean), crab_position);
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << "\n* Results *" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << total_fuel_cost << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << total_crab_fuel_cost << std::endl;
    std::cout << "Calculation took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                                     << " ms" << std::endl;
    return 0;
}