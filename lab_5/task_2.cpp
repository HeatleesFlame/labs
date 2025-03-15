#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


bool isRoot(const std::string& root, const std::string& word) {
    if (root.size() > word.size()) return false;
    return word.substr(0, root.size()) == root;
}

int main(int argc, char **argv) {
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file!" << std::endl;
        return 1;
    }

    std::vector<std::string> words;
    std::string word;
    while (inputFile >> word) {
        words.push_back(word);
    }
    inputFile.close();

    if (words.empty()) {
        std::ofstream outputFile1("output_longest_root.txt");
        std::ofstream outputFile2("output_cool_root.txt");
        outputFile1 << "NO" << std::endl;
        outputFile2 << "NO" << std::endl;
        return 0;
    }


    std::vector<std::pair<std::string, std::vector<std::string>>> rootWords;

    for (const auto& potentialRoot : words) {
        std::vector<std::string> children;
        for (const auto& word : words) {
            if (isRoot(potentialRoot, word) && potentialRoot != word) {
                children.push_back(word);
            }
        }
        if (!children.empty()) {
            rootWords.push_back({potentialRoot, children});
        }
    }

    if (rootWords.empty()) {
        std::ofstream outputFile1("output_longest_root.txt");
        std::ofstream outputFile2("output_cool_root.txt");
        outputFile1 << "NO" << std::endl;
        outputFile2 << "NO" << std::endl;
        return 0;
    }

    auto longestRoot = *std::max_element(rootWords.begin(), rootWords.end(),
        [](const auto& a, const auto& b) {
            return a.first.size() < b.first.size();
        });

    auto mostImportantRoot = *std::max_element(rootWords.begin(), rootWords.end(),
        [](const auto& a, const auto& b) {
            return a.second.size() < b.second.size();
        });

    std::ofstream outputFile1("output_longest_root.txt");
    outputFile1 << longestRoot.first << " ";
    for (const auto& child : longestRoot.second) {
        outputFile1 << child << " ";
    }
    outputFile1 << "\n";

    std::ofstream outputFile2("output_cool_root.txt");
    outputFile2 << mostImportantRoot.first << " " << mostImportantRoot.second.size() << "\n";

    return 0;
}