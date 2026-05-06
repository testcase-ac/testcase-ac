#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
using namespace std;

static std::mt19937_64 seedRng;

static void initSeed(int argc, char* argv[]) {
    unsigned long long seed = argc > 1
        ? std::strtoull(argv[1], nullptr, 10)
        : static_cast<unsigned long long>(std::chrono::steady_clock::now().time_since_epoch().count());
    seedRng.seed(seed);
    std::srand(static_cast<unsigned>(seed));
}

struct seeded_random_device {
    using result_type = unsigned long long;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return ~0ULL; }
    result_type operator()() { return seedRng(); }
};

#define random_device seeded_random_device


vector<string> words = {
    "BaekJoon", "Algorithm", "Contest", "Dynamic Programming", "Greedy", "Graph", "Tree",
    "Queue", "Stack", "PriorityQueue", "BinarySearch", "DFS", "BFS", "Memoization", "Divide And Conquer",
    "MatheMatics", "BitMask", "Set", "Map", "Segment Tree", "HashMap", "Sliding Window", "PrefixSum", 
    "Binary Search Tree", "Union Find", "Topological Sort", "KnapSack", "LIS", "Sieve", "Two Pointer", 
    "BackTracking", "String Matching", "Game Theory", "String", "Simulation", "Recursion"
};

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> num_dis(1, 7);
    uniform_int_distribution<> word_dis(0, words.size() - 1);
    uniform_int_distribution<> num_to_append(1, 9);

    int num_words = num_dis(gen);
    vector<string> selected_words;

    for (int i = 0; i < num_words; ++i) {
        string selected_word = words[word_dis(gen)];
        selected_word += to_string(num_to_append(gen));
        selected_words.push_back(selected_word);
    }
    for (const auto& word : selected_words) {
        cout << word << endl;
    }
    return 0;
}
