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
	uniform_int_distribution<int> n_dist(1, 1000000);
	uniform_int_distribution<long long> m_dist(1, 2000000000);
	uniform_int_distribution<int> h_dist(0, 1000000000);

	int n = n_dist(gen);
	long long m = m_dist(gen);

	cout << n << " " << m << "\n";
	long long sum = 0;
	int heights[n];
	for (int i = 0; i < n; i++) {
		heights[i] = h_dist(gen);
		sum += heights[i];
	}
	while (sum < m) {
		int idx = gen() % n;
		int add = h_dist(gen) % (m - sum + 1);
		sum += add;
		heights[idx] += add;
	}
	for (int i = 0; i < n; i++) {
		cout << heights[i];
		if (i < n - 1) cout << " ";
	}
	return 0;
}
