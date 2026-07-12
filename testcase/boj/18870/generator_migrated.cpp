#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
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
    uniform_int_distribution<> dist(-1000000000, 1000000000);
    uniform_int_distribution<> n_dist(1, 20);

    int N = n_dist(gen);
    vector<int> X(N);
    set<int> unique_values;

    for (int i = 0; i < N; ++i) {
        int x = dist(gen);
        unique_values.insert(x);
    }

    vector<int> unique_X(unique_values.begin(), unique_values.end());
    N = unique_X.size();

    cout << N << "\n";
    for (int i = 0; i < N; ++i) {
        if (i > 0) cout << " ";
        cout << unique_X[i];
    }
    cout << "\n";
}
