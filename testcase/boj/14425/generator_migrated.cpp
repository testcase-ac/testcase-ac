#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <chrono>
#include <random>

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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    vector<string> sample = {
        "baekjoononlinejudge", "startlink", "codeplus", "sundaycoding", "codingsh", 
        "baekjoon", "codeplus", "codeminus", "startlink", "starlink", "sundaycoding", 
        "codingsh", "codinghs", "sondaycoding", "startrink", "icerink", "programming", 
        "algorithm", "datastructures", "contest", "debugging", "compiler", "binarytree"
    };
    
    int N = rand() % 10 + 1;
    int M = rand() % 10 + 1;
    
    cout << N << " " << M << endl;
    
    unordered_set<string> setN;
    unordered_set<string> setM;
    
    for (int i = 0; i < N; ++i) {
        while (true) {
            int idx = rand() % sample.size();
            if (setN.find(sample[idx]) == setN.end()) {
                setN.insert(sample[idx]);
                cout << sample[idx] << endl;
                break;
            }
        }
    }
    
    for (int i = 0; i < M; ++i) {
        while (true) {
            int idx = rand() % sample.size();
            if (setM.find(sample[idx]) == setM.end()) {
                setM.insert(sample[idx]);
                cout << sample[idx] << endl;
                break;
            }
        }
    }
    
    return 0;
}
