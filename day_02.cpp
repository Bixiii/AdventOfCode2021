#include <iostream>
#include <string>
#include <vector>
#include "utils.h"

int main() {
    int challenge_id = 2;
    std::vector<std::string> input_data = InputData(challenge_id);

    int horizontal_position = 0;
    int vertical_position = 0;

    for (const auto &input_data_item : input_data) {
        std::istringstream move_command(input_data_item);
        std::string direction;
        int value;
        move_command >> direction >> value;
        if (direction == "forward") {
            horizontal_position += value;
        }
        else if (direction == "down") {
            vertical_position += value;
        }
        else if (direction == "up") {
            vertical_position -= value;
        }
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << horizontal_position * vertical_position  << std::endl;

    horizontal_position = 0;
    vertical_position = 0;
    int aim = 0;

    for (const auto &input_data_item : input_data) {
        std::istringstream move_command(input_data_item);
        std::string direction;
        int value;
        move_command >> direction >> value;
        if (direction == "forward") {
            horizontal_position += value;
            vertical_position += value*aim;
        }
        else if (direction == "down") {
            aim += value;
        }
        else if (direction == "up") {
            aim -= value;
        }
    }

    std::cout << "Day " << challenge_id << " - Part 2: " << horizontal_position * vertical_position << std::endl;

    return 0;
}