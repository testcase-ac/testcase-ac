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
	int n = rand() % 20 + 1;
	cout << n << endl;
	int last = rand() % 100 + 1;
	cout << last << endl;

	for (int i = 1; i < n; i++) {
		int delta = rand() % (1 << 24);
		last += delta;
		if (last > (1 << 30)) last = (1 << 30);
		cout << last << endl;
	}
}
