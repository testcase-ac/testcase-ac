#include <iostream>
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
    uniform_int_distribution<> dis(1, 1000);

    int x1 = dis(gen), y1 = dis(gen);
    int x2 = dis(gen), y2 = dis(gen);

    while (x1 == x2 || y1 == y2) {
        x2 = dis(gen);
        y2 = dis(gen);
    }

    cout << x1 << " " << y1 << endl;
    cout << x1 << " " << y2 << endl;
    cout << x2 << " " << y1 << endl;

    return 0;
}
