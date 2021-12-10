#include <iostream>
#include <string>
#include "utils.h"
#include <stack>
#include <algorithm>

bool IsOpening(char brace) {
    return brace == '(' || brace == '[' || brace == '{' || brace == '<';
}

bool CorrectClose(char open, char close) {
    return (open == '(' && close == ')') || (open == '[' && close == ']') || (open == '<' && close == '>') ||
        (open == '{' && close == '}');
}

int SyntaxScore(char brace) {
    switch (brace) {
        case ')': return 3;
        case ']': return 57;
        case '}': return 1197;
        case '>': return 25137;
        default: return -1;
    }
}

long long int AutocompleteScore(std::stack<char> open_braces) {
    long long int score = 0;
    while (!open_braces.empty()){
        char brace = open_braces.top();
        open_braces.pop();
        switch (brace) {
            case '(':
                score = score * 5 + 1;
                break;
            case '[':
                score = score * 5 + 2;
                break;
            case '{':
                score = score * 5 + 3;
                break;
            case '<':
                score = score * 5 + 4;
                break;
            default:
                return -1;
        }
    }
    return score;

}

int main() {

    int challenge_id = 10;
    auto input_data = InputData(challenge_id);

    std::vector<std::vector<char>> code_lines;
    for(auto i=0; i < input_data.size(); i++) {
        std::vector<char> code_line;
        for (auto brace : input_data[i]) {
            code_line.emplace_back(brace);
        }
        code_lines.emplace_back(code_line);
    }

    int syntax_score = 0;
    std::vector<long long int> auto_complete_scores;
    for (auto code_line : code_lines) {
        bool corrupted = false;
        std::stack<char> open_braces;
        for (auto brace : code_line) {
            if (IsOpening(brace)) {
                open_braces.emplace(brace);
                continue;
            } else if (CorrectClose(open_braces.top(), brace)){
                open_braces.pop();
                continue;
            }
            // corrupted line detected
            syntax_score += SyntaxScore(brace);
            corrupted = true;
            break;
        }
        if (!corrupted) {
            // uncorrupted line
            auto_complete_scores.emplace_back(AutocompleteScore(std::move(open_braces)));
        }
    }
    std::sort(auto_complete_scores.begin(), auto_complete_scores.end());

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << syntax_score << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << auto_complete_scores[int(auto_complete_scores.size()/2)] << std::endl;

    return 0;
}
