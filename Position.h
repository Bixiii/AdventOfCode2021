//
// Created by bschreiber on 11.05.2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <sstream>

#ifndef ADVENTOFCODE2021__POSITION_H_
#define ADVENTOFCODE2021__POSITION_H_

class Position {

 private:
    int x_;
    int y_;
    inline static int field_size_ = 0;

 public:
    Position () = default;
    Position(int x, int y) : x_(x), y_(y) {};
    static void SetFieldSize(int field_size) {field_size_=field_size;}
    std::vector<Position> Neighbours(bool diagonals);
    std::string Description();

    bool operator==(const Position &rhs) const {
        return x_==rhs.x_ && y_==rhs.y_;
    }
    bool operator<(const Position &rhs) const {
        return std::tie(x_, y_) < std::tie(rhs.x_, rhs.y_);
    }
    [[nodiscard]] std::tuple<int, int> Coordinates() const {
        return std::make_tuple(x_, y_);
    }

    [[nodiscard]] std::string ToString() const {
        std::stringstream build_string;
        build_string << "(" << x_ << "/" << y_ << ")";
        return build_string.str();
    }
};


#endif //ADVENTOFCODE2021__POSITION_H_
