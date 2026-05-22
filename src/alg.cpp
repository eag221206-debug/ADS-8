// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string current_word = "";

    while (true) {
        int ch = file.get();
        
        if (ch == EOF) {
            if (!current_word.empty()) {
                tree.add(current_word);
            }
            break;
        }

        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch + 32;
            }
            current_word += static_cast<char>(ch);
        } else {
            if (!current_word.empty()) {
                tree.add(current_word);
                current_word = "";
            }
        }
    }

    file.close();
}

bool compareByFrequency(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second; 
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> pairs;
    tree.getPairs(pairs);

    std::sort(pairs.begin(), pairs.end(), compareByFrequency);

    std::ofstream outFile("result/freq.txt");

    for (const auto& p : pairs) {
        std::cout << p.first << " - " << p.second << std::endl;
        if (outFile.is_open()) {
            outFile << p.first << " " << p.second << std::endl;
        }
    }

    if (outFile.is_open()) {
        outFile.close();
    }
}
