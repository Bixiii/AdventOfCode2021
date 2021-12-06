#include <iostream>
#include <string>
#include "utils.h"

void simulate_one_day(std::vector<long long int>& fish_accumulator) {
    long long int num_new_fish = fish_accumulator[0];
    for (int i=0; i<fish_accumulator.size()-1; i++){
        fish_accumulator[i]=fish_accumulator[i+1];
    }
    fish_accumulator[fish_accumulator.size()-1] = num_new_fish;
    fish_accumulator[fish_accumulator.size()-3] += num_new_fish;
}

int main() {

    int challenge_id = 6;
    auto input_data = InputData(challenge_id);

    std::string next_fish;
    std::stringstream input_fish_stream(input_data[0]);
    std::vector<long long int> fish_accumulator = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    while (std::getline(input_fish_stream, next_fish, ',')) {
        fish_accumulator[std::stoi(next_fish)]++;
    }

    int simulation_days = 80;
    std::vector<long long int> fish_accumulator_copy(fish_accumulator);
    for (int i=0; i<simulation_days; i++) {
        simulate_one_day(fish_accumulator_copy);
    }

    long long int num_fish = 0;
    for (long long int i : fish_accumulator_copy) {
        num_fish += i;
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << num_fish << std::endl;

    simulation_days = 256;
    for (int i=0; i<simulation_days; i++) {
        simulate_one_day(fish_accumulator);
    }

    num_fish = 0;
    for (long long int i : fish_accumulator) {
        num_fish += i;
    }

    std::cout << "Day " << challenge_id << " - Part 2: " << num_fish << std::endl;

    return 0;
}
