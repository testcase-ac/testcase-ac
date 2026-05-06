#include <iostream>
#include <vector>
#include <random>
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


int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> str_dis(0, 41);
    vector<string> words = {
        "baekjoon", "codeforces", "algorithm", "data", "structure", "programming", "contest", "problem", 
        "solution", "input", "output", "testcase", "example", "judge", "submission", "compile", "debug", 
        "runtime", "time", "space", "complexity", "optimization", "greedy", "dynamic", "programming", 
        "divide", "conquer", "graph", "tree", "search", "sort", "bfs", "dfs", "dp", "bitmask", "segment", 
        "union", "find", "heap", "priority", "queue", "stack", "deque", "map", "set", "hash", "bit", "shiftpsh", "sprout", "pulljima"};
    string selected_word = words[str_dis(gen)];
    uniform_int_distribution<> num_dis(1, selected_word.size()); 
    cout << selected_word << endl;
    return 0;
}
