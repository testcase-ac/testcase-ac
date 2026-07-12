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
    ios::sync_with_stdio(false);
    cout.tie(0);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 99);

    int n = dis(gen)/3+1;
    cout << n << "\n";
    vector<int> X(n), Y(n);
    for (int i = 0; i < n; ++i) {
        X[i] = dis(gen);
    }
    for (int i = 0; i < n; ++i) {
        Y[i] = dis(gen);
    }
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << " ";
        cout << X[i];
    }
    cout << "\n";
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << " ";
        cout << Y[i];
    }
    cout << "\n";
    return 0;
}
