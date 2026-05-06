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
    uniform_int_distribution<> dis_a(1, 1000);
    uniform_int_distribution<> dis_b(1, 999);
    uniform_int_distribution<> dis_v(1, 1000000000);
    
    int A = dis_a(gen);
    int B = dis_b(gen);
    int V = dis_v(gen);
    
    while (A <= B || V <= A) {
        A = dis_a(gen);
        B = dis_b(gen);
        V = dis_v(gen);
    }
    cout << A << " " << B << " " << V << endl;
    return 0;
}
