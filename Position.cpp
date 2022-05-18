//
// Created by bschreiber on 11.05.2022.
//

#include "Position.h"

std::vector<Position> Position::Neighbours() {
    std::vector<Position> neighbours;
    // left
    if(x_-1 >= 0){
        neighbours.emplace_back(x_-1, y_);
    }
    // right
    if(x_+1 < field_size_){
        neighbours.emplace_back(x_+1, y_);
    }
    // down
    if(y_+1 < field_size_){
        neighbours.emplace_back(x_, y_+1);
    }
    // up
    if(y_-1 >= 0){
        neighbours.emplace_back(x_, y_-1);
    }
    // left up
    if (x_-1 >= 0 && y_-1 >= 0) {
        neighbours.emplace_back(x_-1, y_-1);
    }
    // left down
    if (x_-1 >= 0 && y_+1 < field_size_) {
        neighbours.emplace_back(x_-1, y_+1);
    }
    // right up
    if (x_+1 < field_size_ && y_-1 >= 0) {
        neighbours.emplace_back(x_+1, y_-1);
    }
    // right down
    if (x_+1 < field_size_ && y_+1 < field_size_) {
        neighbours.emplace_back(x_+1, y_+1);
    }
    return neighbours;
}

std::string Position::Description() {
    std::stringstream description;
    description << "x=" << x_ << ", y=" << y_;
    return description.str();
}
