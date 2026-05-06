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


string generate_large_number(int digits) {
    string num;
    num += (rand() % 9 + 1) + '0';
    for (int i = 1; i < digits; i++) {
        num += (rand() % 10) + '0';
    }
    return num;
}

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    unsigned seed = seedRng();
    srand(seed);

    int a_digits = rand() % 50 + 20;
    int b_digits = rand() % 50 + 20;
  if(rand()%2) {
    a_digits = rand() % 300000;
    b_digits = rand() % 300000;
  }

    string a = generate_large_number(a_digits);
    string b = generate_large_number(b_digits);

    cout << a << " " << b << endl;

    return 0;
}
