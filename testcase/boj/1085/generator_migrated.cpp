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
	uniform_int_distribution<> dis_w(2, 1000);
	uniform_int_distribution<> dis_h(2, 1000);

	int w = dis_w(gen);
	int h = dis_h(gen);

	uniform_int_distribution<> dis_x(1, w - 1);
	uniform_int_distribution<> dis_y(1, h - 1);

	int x = dis_x(gen);
	int y = dis_y(gen);

	cout << x << " " << y << " " << w << " " << h << endl;
}
