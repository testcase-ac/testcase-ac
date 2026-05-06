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
	mt19937_64 gen(rd());
	uniform_int_distribution<int> f(0,1);
	uniform_int_distribution<int> x(1,15);
	uniform_int_distribution<int> y(1,100000);
	uniform_int_distribution<int> n(2,500000);
	int t;
	if(f(gen)) t=x(gen);
	else t=y(gen);
	cout<<t<<'\n';
	while(t--) cout<<n(gen)*2<<'\n';
}
