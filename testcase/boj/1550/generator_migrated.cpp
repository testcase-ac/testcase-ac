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


string random_hex() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> len_dist(1, 6);
	uniform_int_distribution<> dist(0, 15);

	int len = len_dist(gen);
	string hex_chars = "0123456789ABCDEF";
	string res = "";
	
	for (int i = 0; i < len; i++) {
		if (i == 0 && len > 1) {
			res += hex_chars[uniform_int_distribution<>(1, 15)(gen)];
		} else {
			res += hex_chars[dist(gen)];
		}
	}
	return res;
}
int main(int argc, char* argv[]) {
    initSeed(argc, argv);
	cout << random_hex() << endl;
	return 0;
}
