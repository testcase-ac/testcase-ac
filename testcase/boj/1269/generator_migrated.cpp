#include <iostream>
#include <vector>
#include <random>
#include <set>
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
	uniform_int_distribution<int> d1(1, 15);
	uniform_int_distribution<int> d2(1, 1000000);
	uniform_int_distribution<int> d3(0, 2); 

	int n = d1(gen), m = d1(gen);
	cout << n << ' ' << m << '\n';

	vector<int> common;
	set<int> a, b;

	while (a.size() < n) {
		int v = d2(gen);
		if (!common.empty() && d3(gen) == 0) v = common[d3(gen) % common.size()];
		a.insert(v);
		common.push_back(v);
	}

	while (b.size() < m) {
		int v = d2(gen);
		if (!common.empty() && d3(gen) == 0) v = common[d3(gen) % common.size()];
		b.insert(v);
	}

	for (int v : a) cout << v << ' ';
	cout << '\n';
	for (int v : b) cout << v << ' ';
}
