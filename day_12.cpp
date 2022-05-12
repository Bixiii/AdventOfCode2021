#include <iostream>
#include <string>
#include "utils.h"
#include <list>
#include <map>
#include <utility>
#include <cctype>
#include <sstream>

std::list<std::string> path_description_;

void print_path() {
    std::stringstream path;
    for (auto sub_path : path_description_) {
        path << sub_path;
    }
    std::cout << path.str() << std::endl;
}

bool revisit_used;

class Cave {
 private:
    std::string name_;
    std::list<Cave*> connected_caves_;
    bool visited_ = false;
    bool revisited_ = false;
    bool is_small = false;
 public:
    Cave() = default;
    Cave(std::string name) {
        is_small = islower(name[0]);
        name_ = std::move(name);
        revisit_used = false;
    };

    void AddConnectedCave(Cave* connectedCave) {
        connected_caves_.emplace_back(connectedCave);
    }
    /**
     * Vist the cave if it can be visit and explore all adjacent caves
     * @return true if exploration is finished (either cave can't be entered or stop is reached, false otherwise
     */

    bool operator==(const Cave &rhs) const {
        return name_==rhs.name_;
    }
    bool operator!=(const Cave &rhs) const {
        return !(rhs==*this);
    };
    bool operator<(const Cave &rhs) const {
        return !(name_<rhs.name_);
    };

    int Explore(std::map<std::string, Cave> caves, bool enable_revisit) {
        int found_paths = 0;
        if (is_small) {
            // end reached
            if (name_ == "end") {
                path_description_.emplace_back(" = end");
//                print_path();
                path_description_.pop_back();
                return 1;
            }
            // cave was already visited
            if (caves[name_].visited_){
                if (enable_revisit && (!revisit_used and name_ != "start")) {
                    revisit_used = true;
                    caves[name_].revisited_ = true;
                } else {
                    path_description_.emplace_back(" = blind end");
                    path_description_.pop_back();
                    return 0;
                }
            }
            caves[name_].visited_ = true;
            for (auto connected_cave : connected_caves_) {
                std::stringstream sub_path;
                sub_path << name_ << "->" << connected_cave->name_ << "; ";
                path_description_.emplace_back(sub_path.str());
                found_paths += connected_cave->Explore(caves, enable_revisit);
                path_description_.pop_back();
            }
            if (enable_revisit && caves[name_].revisited_) {
                revisit_used = false;
            }
            return found_paths;
        } else {
            for (auto connected_cave : connected_caves_) {
                std::stringstream sub_path;
                sub_path << name_ << "->" << connected_cave->name_ << "; ";
                path_description_.emplace_back(sub_path.str());
                found_paths += connected_cave->Explore(caves, enable_revisit);
                path_description_.pop_back();
            }
            return found_paths;
        }
    }
};

int main() {

    int challenge_id = 12;
    auto input_data = InputData(challenge_id);
    std::map<std::string, Cave> caves = {};

    for(auto i=0; i < input_data.size(); i++) {
        std::string start = input_data[i].substr(0, input_data[i].find('-'));
        std::string end = input_data[i].substr(input_data[i].find('-')+1);
        if (caves.count(start) <= 0) {
            if (isupper(start[0])) {
                caves[start] = Cave(start);
            } else {
                caves[start] = Cave(start);
            }
        }
        if (caves.count(end) <= 0) {
            if (isupper(end[0])) {
                caves[end] = Cave(end);
            } else {
                caves[end] = Cave(end);
            }
        }
        caves[start].AddConnectedCave(&caves[end]);
        caves[end].AddConnectedCave(&caves[start]);
    }

    // part 1
    int res_one = caves["start"].Explore(caves, false);
    // part 2
    int res_two = caves["start"].Explore(caves, true);

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << res_one << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << res_two << std::endl;

    return 0;
}
