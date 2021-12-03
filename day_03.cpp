#include <iostream>
#include <string>
#include "utils.h"

int ToDecimal(const int binary[], const int len) {
    int output = 0;
    int power = 1;
    for(int i=0; i<len; i++) {
        output += binary[(len - 1) - i] * power;
        power *= 2;
    }
    return output;
}

int ToDecimal(const std::string &binary) {
    int output = 0;
    int power = 1;
    std::string reversed = binary;
    std::reverse(reversed.begin(), reversed.end());
    for(auto bit : reversed) {
        output += ((int)bit-48) * power;
        power *= 2;
    }
    return output;
}

int main() {

    const int kDataSize = 12;

    int challenge_id = 3;

    std::vector<std::string> input_data = InputData(challenge_id);

    int gamma_count[kDataSize] = {0};
    int epsilon_count[kDataSize] = {0};

    for(auto input_item : input_data) {
        for(int i=0; i < input_item.length(); i++) {
            if((int)input_item[i]-48 == 1) {
                gamma_count[i]++;
            } else {
                epsilon_count[i]++;
            }
        }
    }

    int gamma[kDataSize] = {0};
    int epsilon[kDataSize] = {0};

    for (int i=0; i<kDataSize; i++) {
        if(gamma_count[i] > epsilon_count[i]) {
            gamma[i] = 1;
        } else if(gamma_count[i] < epsilon_count[i]) {
            epsilon[i] = 1;
        } else {
            std::cout << "WARN: they are equal" << std::endl;
        }
    }

    int gamma_value = ToDecimal(gamma, kDataSize);
    int epsilon_value = ToDecimal(epsilon, kDataSize);

    std::cout << "\nDay 3 - Part 1: " << gamma_value * epsilon_value << std::endl;

    // --- PART 2 ---

    std::vector<int> oxygen_idx;
    oxygen_idx.reserve(input_data.size());
    for(int i=0; i<input_data.size(); i++){
        oxygen_idx.emplace_back(i);
    }

    std::vector<int> ones;
    std::vector<int> zeros;

    for (int i=0; i<kDataSize; i++) {

        ones.clear();
        zeros.clear();

        for (auto idx : oxygen_idx) {
            if((int)input_data[idx][i]-48 == 1) {
                ones.emplace_back(idx);
            } else {
                zeros.emplace_back(idx);
            }
        }

        oxygen_idx.clear();
        if(zeros.size() > ones.size()) {
            oxygen_idx = zeros;
        } else {
            oxygen_idx = ones;
        }
        if(oxygen_idx.size() == 1){
            break;
        }
    }

    std::string oxygen_rating = input_data[oxygen_idx[0]];

    std::vector<int> co2_idx;
    co2_idx.reserve(input_data.size());
    for(int i=0; i<input_data.size(); i++){
        co2_idx.emplace_back(i);
    }

    for (int i=0; i<kDataSize; i++) {

        ones.clear();
        zeros.clear();

        for (auto idx : co2_idx) {
            if((int)input_data[idx][i]-48 == 1) {
                ones.emplace_back(idx);
            } else {
                zeros.emplace_back(idx);
            }
        }

        co2_idx.clear();
        if(zeros.size() <= ones.size()) {
            co2_idx = zeros;
        } else {
            co2_idx = ones;
        }
        if(co2_idx.size() == 1) {
            break;
        }
    }

    std::string co2_rating = input_data[co2_idx[0]];

    std::cout << "Day 3 - Part 2: " << ToDecimal(oxygen_rating) * ToDecimal(co2_rating) << std::endl;

    return 0;
}