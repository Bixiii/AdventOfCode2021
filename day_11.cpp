#include <iostream>
#include <string>
#include "utils.h"
#include <list>
#include <map>

int field_size = 10;
class Position {
 private:
  int x_;
  int y_;
 public:
    Position () = default;
    Position(int x, int y) : x_(x), y_(y) {};
    std::vector<Position> Neighbours() {
        std::vector<Position> neighbours;
        // left
        if(x_-1 >= 0){
            neighbours.emplace_back(x_-1, y_);
        }
        // right
        if(x_+1 < field_size){
            neighbours.emplace_back(x_+1, y_);
        }
        // down
        if(y_+1 < field_size){
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
        if (x_-1 >= 0 && y_+1 < field_size) {
            neighbours.emplace_back(x_-1, y_+1);
        }
        // right up
        if (x_+1 < field_size && y_-1 >= 0) {
            neighbours.emplace_back(x_+1, y_-1);
        }
        // right down
        if (x_+1 < field_size && y_+1 < field_size) {
            neighbours.emplace_back(x_+1, y_+1);
        }
        return neighbours;
    };

    bool operator==(const Position &rhs) const {
        return x_==rhs.x_ && y_==rhs.y_;
    }
    bool operator<(const Position &rhs) const {
        return std::tie(x_, y_) < std::tie(rhs.x_, rhs.y_);
    }

    std::string Description(){
        std::stringstream description;
        description << "x=" << x_ << ", y=" << y_;
        return description.str();
    }

};

class Octopus {
 private:
    int energy_level_;
    bool flashed_ = false;
 public:
    Octopus () = default;
    Octopus(int energy_level) : energy_level_(energy_level) {}
    int EnergyLevel(){
        return energy_level_;
    }
    /**
     * Increase energy by one
     * @return true if octopus flashes
     */
    bool IncrementEnergyLevelInCurrentCycle(){
        if (flashed_) { // only flash once per cycle
            return false;
        }
        energy_level_++;
        if (energy_level_ > 9){
            energy_level_ = 0;
            flashed_ = true;
            return true;
        }
        return false;
    }

    void StartNextCycle() {
        flashed_ = false;
    }

};

int main() {

    int challenge_id = 11;
    auto input_data = InputData(challenge_id);


    std::map<Position, Octopus> octopus_field;

    for(int x=0; x<field_size; x++) { // row = y coordinate
        for(int y=0; y<field_size; y++) { // column = x coordinate
            Position position = Position {x, y};
            Octopus octopus(((int) input_data[x][y] - 48));
            octopus_field[position] = octopus;
        }
    }

    int num_flashes = 0;
    int num_flashes_after_100_cycles = 0;
    int current_cycle = 0;
    int num_all_flashed_cycle = 0;

    while (true) {

        if (current_cycle == 100) {
            num_flashes_after_100_cycles = num_flashes;
        }
        current_cycle++;

        bool all_flashed = true;
        for (int x=0; x<field_size; x++){
            for (int y=0; y<field_size; y++){
                if (octopus_field[Position{x,y}].EnergyLevel() != 0){
                    all_flashed = false;
                    break;
                }
            }
        }
        if (all_flashed) {
            num_all_flashed_cycle = current_cycle;
            break;
        }

        std::vector<Position> needs_increment = {};
        std::vector<Position> neighbour_flashed = {};

        for (int x=0; x<field_size; x++) {
            for (int y=0; y<field_size; y++) {
                Position position = {x, y};
                if (octopus_field[position].IncrementEnergyLevelInCurrentCycle()) {
                    std::vector<Position> neighbours = position.Neighbours();
                    neighbour_flashed.insert(neighbour_flashed.end(), neighbours.begin(), neighbours.end());
                    num_flashes++;
                }
            }
        }

        needs_increment = neighbour_flashed;
        while (!needs_increment.empty()){
            needs_increment = neighbour_flashed;
            neighbour_flashed = {};
            for (Position position : needs_increment) {
                if (octopus_field[position].IncrementEnergyLevelInCurrentCycle()) {
                    std::vector<Position> neighbours = position.Neighbours();
                    neighbour_flashed.insert(neighbour_flashed.end(), neighbours.begin(), neighbours.end());
                    num_flashes++;
                }
            }
        }

        for (int x=0; x<field_size; x++) {
            for (int y=0; y<field_size; y++) {
                Position position = {x, y};
                octopus_field[position].StartNextCycle();
            }
        }
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << num_flashes_after_100_cycles << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << num_all_flashed_cycle-1 << std::endl;

    return 0;
}
