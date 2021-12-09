#include <iostream>
#include <string>
#include "utils.h"

int main() {

    int challenge_id = 8;
    auto input_data = InputData(challenge_id);

    for(auto i=0; i < input_data.size(); i++) {
        std::cout << input_data[i] << std::endl;
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << std::endl;

    return 0;
}
