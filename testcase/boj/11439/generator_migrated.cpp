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
    long long n = rand() % 4000000 + 1;
    long long k = rand() % (n + 1);
    int m = rand() % 4000000 + 2;
    cout << n << " " << k << " " << m << endl;
    return 0;
}
