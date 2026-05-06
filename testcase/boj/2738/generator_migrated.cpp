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


int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> size_dis(1, 8);
    int N = size_dis(gen);
    int M = size_dis(gen);
    uniform_int_distribution<> value_dis(-100, 100);

    cout << N << " " << M << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << value_dis(gen) << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << value_dis(gen) << " ";
        }
        cout << endl;
    } return 0;
}
