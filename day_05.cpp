#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <tuple>
#include "utils.h"


typedef struct Point{
    int x;
    int y;

    bool operator == (const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator < (const Point& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
} Point;

void AddVentsToMap(const Point start, const Point stop, std::map<Point, int> &vent_fields, bool count_diagonals= false){
    // horizontal lines
    if (start.x == stop.x) {
        for (int y=std::min(start.y,stop.y); y<=std::max(start.y,stop.y); y++) {
            Point current_pos = {start.x, y};
            if (!vent_fields.contains(current_pos)) {
                vent_fields[current_pos] = 0;
            }
            vent_fields[current_pos]++;
        }
    // vertical lines
    } else if (start.y == stop.y) {
        for (int x=std::min(start.x,stop.x); x<=std::max(start.x,stop.x); x++) {
            Point current_pos = {x, start.y};
            if (!vent_fields.contains(current_pos)) {
                vent_fields[current_pos] = 0;
            }
            vent_fields[current_pos]++;
        }
    // diagonal lines
    } else if (count_diagonals){
        auto left = std::min(start, stop);
        auto right = std::max(start, stop);
        int len = right.x - left.x;
        for (int step=0; step<=len; step++) {
            Point current_pos;
            if (left.y < right.y) { // down
                current_pos = {left.x + step, left.y + step};
            }
            else { // down
                current_pos = {left.x + step, left.y - step};
            }
            if (!vent_fields.contains(current_pos)) {
                vent_fields[current_pos] = 0;
            }
            vent_fields[current_pos]++;
        }
    }
}

int NumDangerZones(std::map<Point, int> &vent_fields) {
    int danger_zones = 0;
    for (const auto& [k,v] : vent_fields) {
        if (v > 1) {
            danger_zones++;
        }
    }
    return danger_zones;
}

int main() {

    int challenge_id = 5;
    auto input_data = InputData(challenge_id);

    std::map<Point, int> vent_fields;
    for(auto & input_item : input_data) {
        int x1, x2, y1, y2;
        sscanf_s(input_item.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
        AddVentsToMap(Point{x1, y1}, Point{x2, y2}, vent_fields);
    }
    std::cout << "Day " << challenge_id << " - Part 1: " << NumDangerZones(vent_fields) << std::endl;

    vent_fields.clear();
    for(auto & input_item : input_data) {
        int x1, x2, y1, y2;
        sscanf_s(input_item.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
        AddVentsToMap(Point{x1, y1}, Point{x2, y2}, vent_fields, true);
    }
    std::cout << "Day " << challenge_id << " - Part 2: " << NumDangerZones(vent_fields) << std::endl;

    return 0;
}
