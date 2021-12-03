#include "utils.h"

std::vector<std::string> InputData(int challenge_id){
    std::stringstream data_path_stream;
    data_path_stream << "input_day_" << challenge_id << ".txt";
    std::string data_path = data_path_stream.str();
    std::ifstream input_file(data_path);
    std::string line;
    std::vector<std::string> input_data;
    while(std::getline(input_file, line)) {
        input_data.emplace_back(line);
    }
    return input_data;

}
