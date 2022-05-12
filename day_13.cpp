#include <iostream>
#include <string>
#include "utils.h"
#include "Position.h"

class Dot {
 private:
    Position position_;
 public:
    Dot(const Position &position) : position_(position) {};
    std::tuple<int, int> Coordinates() {
        return position_.Coordinates();
    }
    // vertical
    void FoldX(int fold_line) {
        auto [x, y] = position_.Coordinates();
        if (x>fold_line) {
            int new_x = fold_line - (x - fold_line);
            if (new_x < 0) {
            }
            position_ = Position(new_x, y);
        }
    }
    // horizontal
    void FoldY(int fold_line) {
        auto [x, y] = position_.Coordinates();
        if (y>fold_line) {
            int new_y = fold_line - (y - fold_line);
            if (new_y < 0) {
            }
            position_ = Position(x, new_y);
        }
    }
};

std::vector<std::vector<char>> EmptyFieldDrawing(int x_max, int y_max) {
    std::vector<std::vector<char>> field_drawing;
    field_drawing.reserve(y_max);
    for (int y=0; y<y_max; y++) {
        std::vector<char> line;
        line.reserve(x_max);
        for (int x=0; x<x_max; x++) {
            line.emplace_back(' ');
        }
        field_drawing.emplace_back(std::move(line));
    }
    return std::move(field_drawing);
}

void MarkDots(std::vector<std::vector<char>>& field, std::vector<Dot>& dots) {
    for (auto& dot : dots) {
        auto [y, x] = dot.Coordinates();
        field[x][y] = 'O';
    }
}

void DrawField(const std::vector<std::vector<char>>& field) {
    std::cout << std::endl;
    for (int y=0; y<field.size(); y++) {
        for (int x=0; x<field[0].size(); x++) {
            std::cout << field[y][x];
        }
        std::cout << std::endl;
    }
}


int main() {

    int challenge_id = 13;
    auto input_data = InputData(challenge_id);

    std::vector<Dot> dots;
    std::vector<std::string> fold_instructions;
    int x_max_idx = 0;
    int y_max_idx = 0;

    bool first_section = true;
    for(auto i=0; i < input_data.size(); i++) {
        if (input_data[i].length() == 0) {
            first_section = false;
            continue;
        }
        if (first_section) {
            int x = std::stoi(input_data[i].substr(0, input_data[i].find(',')));
            int y = std::stoi(input_data[i].substr(input_data[i].find(',')+1));
            if (x > x_max_idx) {
                x_max_idx = x;
            }
            if (y > y_max_idx) {
                y_max_idx = y;
            }
            dots.emplace_back(Position(x ,y));
        } else {
            fold_instructions.emplace_back(input_data[i]);
        }
    }
    int x_max = x_max_idx + 1;
    int y_max = y_max_idx + 1;

    std::vector<std::vector<char>> field_drawing;

    bool first_fold = true;
    int num_dots_after_first_fold = 0;

    for (auto fold_instruction : fold_instructions) {
        char direction = fold_instruction[fold_instruction.find('=') - 1];
        int fold_line = std::stoi(fold_instruction.substr(fold_instruction.find('=') + 1));
        if (direction == 'x') {
            std::cout << "Fold along x=" << fold_line << std::endl;
            for (auto& dot : dots) {
                dot.FoldX(fold_line);
            }
            x_max = x_max - fold_line - 1;
        } else {
            std::cout << "Fold along y=" << fold_line << std::endl;
            for (auto& dot : dots) {
                dot.FoldY(fold_line);
            }
            y_max = y_max - fold_line - 1;
        }
        if (first_fold) {
            first_fold = false;
            field_drawing = EmptyFieldDrawing(x_max, y_max);
            MarkDots(field_drawing, dots);
            for (auto& line : field_drawing) {
                for (auto& symbol : line) {
                    if (symbol == 'O') {
                        num_dots_after_first_fold++;
                    }
                }
            }
        }
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << num_dots_after_first_fold << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: ";
    field_drawing = EmptyFieldDrawing(x_max, y_max);
    MarkDots(field_drawing, dots);
    DrawField(field_drawing);

    return 0;
}
