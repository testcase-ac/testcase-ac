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
    uniform_int_distribution<> dist(0, 3);

    int case_type = dist(gen);

    int a, b, c;
    if (case_type == 0) {
        a = b = c = 60;
    } else if (case_type == 1) {
        a = 60;
        uniform_int_distribution<> angle_dist(1, 89);
        b = angle_dist(gen);
        c = 180 - a - b;
    } else if (case_type == 2) {
        uniform_int_distribution<> angle_dist(1, 178);
        do {
            a = angle_dist(gen);
            b = angle_dist(gen);
            c = 180 - a - b;
        } while (a == b || b == c || a == c || c <= 0);
    } else { // Error
        uniform_int_distribution<> angle_dist(1, 179);
        a = angle_dist(gen);
        b = angle_dist(gen);
        c = angle_dist(gen);
        while (a + b + c == 180) {
            a = angle_dist(gen);
            b = angle_dist(gen);
            c = angle_dist(gen);
        }
    }
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
}
