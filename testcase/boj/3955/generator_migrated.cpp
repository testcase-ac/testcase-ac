#include <iostream>
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
    int t = rand() % 15 + 1;
    cout << t << endl;
    for (int i = 0; i < t/3; ++i) {
        long long k = rand() % 1000 + 1;
        long long c = rand() % 1000 + 1;
        cout << k << " " << c << endl;
    } for (int i = t/3; i < 2*t/3; ++i) {
        long long k = rand() % 1000000 + 1;
        long long c = rand() % 1000000 + 1;
        cout << k << " " << c << endl;
    } for (int i = 2*t/3; i < t; ++i) {
        long long k = rand() % 1000000000 + 1;
        long long c = rand() % 1000000000 + 1;
        cout << k << " " << c << endl;
    }
    return 0;
}
