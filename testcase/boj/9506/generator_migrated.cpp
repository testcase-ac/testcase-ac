#include <iostream>
#include <random>
#include <vector>
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


vector<int> perfect_numbers = {6, 28, 496, 8128};
uniform_int_distribution<> dis(1, 100000);

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> perfect_dis(0, 5);

    while (true) {
        int random_value = dis(gen);
        
        if (random_value <= 10000) {
            cout << -1 << endl;
            break;
        }
        
        if (perfect_dis(gen) == 0) {
            cout << perfect_numbers[dis(gen) % perfect_numbers.size()] << endl;
        } else {
            cout << dis(gen) << endl;
        }
    }
}
