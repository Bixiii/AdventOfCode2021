#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <list>
#include "utils.h"
#include "Position.h"


class Vertex {
 public:
  int x_ = -1;
  int y_ = -1;

  Vertex() = default;

  Vertex(int x, int y) : x_(x), y_(y) {};

  bool operator==(const Vertex &rhs) const {
    return x_==rhs.x_ && y_==rhs.y_;

  }
  bool operator!=(const Vertex &rhs) const {
      return !(rhs==*this);
  }

  std::vector<Vertex> connected_vertices(Vertex vertex, int max_x, int max_y) {
      std::vector<Vertex> connected_vertices;

      auto [x, y] = vertex;

      // left
      if(x-1 >= 0){
          connected_vertices.emplace_back(x-1, y);
      }
      // right
      if(x+1 < max_x){
          connected_vertices.emplace_back(x+1, y);
      }
      // down
      if(y+1 < max_y){
          connected_vertices.emplace_back(x, y+1);
      }
      // up
      if(y-1 >= 0){
          connected_vertices.emplace_back(x, y-1);
      }
      return connected_vertices;
  }

};

int main() {

    int challenge_id = 15;
    auto input_data = InputData(challenge_id);

    int max_y = (int) input_data.size();
    int max_x = (int) input_data[0].size();

    std::vector<std::vector<int>> risk_levels(max_x, std::vector<int>(max_y));
    std::vector<std::vector<int>> distances(max_x, std::vector<int>(max_y));
    std::vector<std::vector<Vertex>> previous(max_x, std::vector<Vertex>(max_y));
    std::vector<Vertex> queue;

    for(auto row=0; row < input_data.size(); row++) {
        for (auto column=0; column < input_data[0].size(); column++) {
            int risk_level = (int)(input_data[row][column] - '0');
            risk_levels[row][column] = risk_level;
        }
    }

    for (int x=0; x<max_x; x++) {
        for (int y=0; y<max_y; y++) {
            distances[x][y] = 2147483646;
            queue.emplace_back(x, y);
//            std::cout << risk_levels[x][y];
        }
//        std::cout << std::endl;
    }

    distances[0][0] = 0;

    int total_iterations = queue.size();
    int percent_for_one_load_line = total_iterations / 80;
    int current_value_percent = percent_for_one_load_line;
    std::cout << std::endl << "Calculating ... " << std::endl;
    int step = 0;
    while (!queue.empty()) {
        int min_dist = 2147483646;
        Vertex closest_vertex;
        for (auto vertex : queue) {
            auto [x,y] = vertex;
            if (distances[x][y] <= min_dist) {
                min_dist = distances[x][y];
                closest_vertex = Vertex(x, y);
            }
        }
        auto closest_vertex_idx = std::find(queue.begin(), queue.end(), closest_vertex);
        if (closest_vertex_idx != queue.end()) {
            queue.erase(closest_vertex_idx);
        }

        for (auto neighbour : closest_vertex.connected_vertices(closest_vertex, max_x, max_y)) {
            if (std::find(queue.begin(), queue.end(), neighbour) != queue.end()) {
                int distance = distances[closest_vertex.x_][closest_vertex.y_] + risk_levels[neighbour.x_][neighbour.y_];
                if (distance < distances[neighbour.x_][neighbour.y_]) {
                    distances[neighbour.x_][neighbour.y_] = distance;
                    previous[neighbour.x_][neighbour.y_] = closest_vertex;
                }
            }
        }

//        std::cout << (max_x * max_y) - (step++) << "|";
        step++;
        if (step > current_value_percent) {
            std::cout << "|";
            current_value_percent+=percent_for_one_load_line;
        }
    }
    std::cout << std::endl << "... finished." << std::endl;


    std::vector<std::vector<std::string>> path(max_x, std::vector<std::string>(max_y));
    for (int x=0; x<max_x; x++) {
        for (int y = 0; y < max_y; y++) {
            path[x][y] = " . ";
        }
    }
    path[max_x-1][max_y-1] = " * ";
    path[0][0] = " * ";

    Vertex current_vertex = Vertex(max_x-1, max_y-1);
    bool path_found = false;
    while (true) {
        auto neighbours = current_vertex.connected_vertices(current_vertex, max_x, max_y);
        int min_dist = 2147483646;
        Vertex closest_vertex;
        for (auto neighbour : neighbours) {
            if (neighbour == Vertex(0,0)){
                path_found = true;
                break;
            }
            if (distances[neighbour.x_][neighbour.y_] < min_dist) {
                min_dist = distances[neighbour.x_][neighbour.y_];
                closest_vertex = neighbour;
            }
        }
        if (path_found) {
            break;
        }
        path[closest_vertex.x_][closest_vertex.y_] = " * ";
        current_vertex = closest_vertex;
    }
//    std::cout << std::endl << "Distances:" << std::endl << "   ";
//    for (int x=0; x<max_x; x++) {
//        std::cout << " " << x << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "---";
//    for (int x=0; x<max_x; x++) {
//        std::cout << "---";
//    }
//    std::cout << std::endl;
//    for (int x=0; x<max_x; x++) {
//        std::cout << x << "| ";
//        for (int y = 0; y < max_y; y++) {
//            if (distances[x][y] < 10) {
//                std::cout << " " << distances[x][y] << " ";
//            } else {
//                std::cout << distances[x][y] << " ";
//            }
//        }
//        std::cout << std::endl;
//    }

    std::cout << std::endl << "Path:" << std::endl << "   ";
    for (int x=0; x<max_x; x++) {
        std::cout << " " << x << " ";
    }
    std::cout << std::endl;
    std::cout << "---";
    for (int x=0; x<max_x; x++) {
        std::cout << "---";
    }
    std::cout << std::endl;
    for (int x=0; x<max_x; x++) {
        std::cout << x << "| ";
        for (int y = 0; y < max_y; y++) {
            std::cout << path[x][y];
        }
        std::cout << std::endl;
    }



    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << distances[max_x-1][max_y-1] << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << std::endl;

    return 0;
}
