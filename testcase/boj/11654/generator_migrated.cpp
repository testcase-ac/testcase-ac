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
    uniform_int_distribution<> char_dis(0, 61);

    char random_char;
    int rand_index = char_dis(gen);
    if (rand_index < 26) {
        random_char = 'a' + rand_index;
    } else if (rand_index < 52) {
        random_char = 'A' + (rand_index - 26);
    } else {
        random_char = '0' + (rand_index - 52);
    }

    cout << random_char << endl;
    return 0;
}
