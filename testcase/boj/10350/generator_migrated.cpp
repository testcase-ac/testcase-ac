#include <iostream>
#include <vector>
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
    unsigned seed = seedRng();
    srand(seed);

    int n = rand() % 10 + 1;
    cout << n << endl;

    vector<int> capitals(n);
    int sum = 0;

    do {
        sum = 0;
        for (int i = 0; i < n; i++) {
            capitals[i] = rand() % 2001 - 1000;
            sum += capitals[i];
        }
    } while (sum <= 0);

    for (int i = 0; i < n; i++) {
        cout << capitals[i];
        if (i < n - 1) cout << ' ';
    }
    cout << endl;

    return 0;
}
