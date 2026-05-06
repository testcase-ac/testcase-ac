#include <iostream>
#include <random>
#include <ctime>
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
    uniform_int_distribution<> dis(1, 5);
    uniform_int_distribution<> dis_size(1, 10);
    uniform_int_distribution<> dis_seat(0, 1);

    int C = dis(gen);
    cout << C << endl;

    for (int i = 0; i < C; ++i) {
        int N = dis_size(gen);
        int M = dis_size(gen);
        cout << N << " " << M << endl;

        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < M; ++k) {
                char seat = dis_seat(gen) == 0 ? '.' : 'x';
                cout << seat;
            }
            cout << endl;
        }
    }

    return 0;
}
