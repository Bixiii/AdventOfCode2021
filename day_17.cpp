#include <iostream>
#include <string>
#include "utils.h"
#include <fstream>

std::ofstream trajectory_points;

class Vector {
 private:
    int x_;
    int y_;

 public:
    Vector(int x, int y) : x_(x), y_(y) {}
    Vector operator+(Vector& other) const {
        return {this->x_+other.x_, this->y_+other.y_};
    }

    void print() const{
        std::cout << "x=" << x_ << ", y=" << y_ << std::endl;
    }

    void x_increment(int value=1){
        x_ += value;
    }
    void y_increment(int value=1){
        y_ += value;
    }
    void x_decrement(int value=1){
        x_increment(-value);
    }
    void y_decrement(int value=1){
        y_increment(-value);
    }

    void x_step_to_zero(int value=1) {
        if (x_ > 0) {
            x_decrement(value);
        } else if (x_ < 0) {
            x_increment(value);
        }
    }

    bool x_inside(int x_min, int x_max) {
        return x_ >= x_min && x_ <= x_max;
    }
    bool y_inside(int y_min, int y_max) {
        return y_ >= y_min && y_ <= y_max;
    }

    int X_(){
        return x_;
    }
    int Y_(){
        return y_;
    }

};

struct TrajectoryParameters {
  bool target_hit;
  int max_y;
} typedef TrajectoryParameters;

TrajectoryParameters shoot_probe(Vector position, Vector velocity, int x_min, int x_max, int y_min, int y_max, bool print=false){
    bool target_hit = false;
    int max_y = 0;
    position = position + velocity;
    if (print) {
        position.print();
    }
    while(true) {
        if (position.Y_() > max_y) {
            max_y = position.Y_();
        }
        if (position.x_inside(x_min, x_max) && position.y_inside(y_min, y_max)) {
            if (print) {
                std::cout << "Hit target!" << std::endl;
            }
            target_hit = true;
            break;
        }
        if (!position.x_inside(INT32_MIN, x_max) || !position.y_inside(y_min, INT32_MAX)) {
            if (print) {
                std::cout << "Overshoot target!" << std::endl;
            }
            break;
        }
        velocity.x_step_to_zero();
        velocity.y_decrement();
        position = position + velocity;
        if (print){
            position.print();
            trajectory_points << position.X_() << ", " << position.Y_() << "\n";
        }
    }
    return {target_hit, max_y};
}


int main() {

    trajectory_points.open("points.csv");

    int challenge_id = 17;

    int target_x_min = 128;
    int target_x_max = 160;
    int target_y_min = -142;
    int target_y_max = -88;

    // find the minimum velocity in x direction that is needed to hit the target
    int x_min_velocity = 0;
    while(true) {
        x_min_velocity ++;
        int max_distance = 0;
        int remaining_velocity = x_min_velocity;
        while (remaining_velocity > 0){
            max_distance += remaining_velocity;
            remaining_velocity--;
        }
        if(max_distance>=target_x_min){
            break;
        }
    }

    // find the maximum velocity in y direction that is possible to not overshoot the target
    int y_velocity = 1;
    int y_max_velocity = 0;
    while(true){
        auto trajectory = shoot_probe(Vector(0, 0), Vector(x_min_velocity, y_velocity), target_x_min, target_x_max, target_y_min, target_y_max, false);
        if (trajectory.target_hit) {
            if (y_max_velocity < y_velocity) {
                y_max_velocity = y_velocity;
            }
        }
        if (y_velocity > (-1*target_y_min)) {
            break;
        }
        y_velocity++;
    }

    // trajectory with highest y value reachable
    auto trajectory = shoot_probe(Vector(0, 0), Vector(x_min_velocity, y_max_velocity), target_x_min, target_x_max, target_y_min, target_y_max, false);


    int valid_velocity_values = 0;
    for (int i=x_min_velocity; i<=target_x_max; i++) {
        int test_y_velocity = target_y_min;
        while(true){
            auto test_trajectory = shoot_probe(Vector(0, 0), Vector(i, test_y_velocity), target_x_min, target_x_max, target_y_min, target_y_max, false);
            if (test_trajectory.target_hit) {
                valid_velocity_values++;
            }
            if (test_y_velocity > (-1*target_y_min)) {
                break;
            }
            test_y_velocity++;
        }
    }


    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: velocity = (x=" << x_min_velocity << ", y=" << y_max_velocity << "), max height = " << trajectory.max_y << std::endl;

    std::cout << "Day " << challenge_id << " - Part 2: " << valid_velocity_values << std::endl;

    trajectory_points.close();

    return 0;
}
