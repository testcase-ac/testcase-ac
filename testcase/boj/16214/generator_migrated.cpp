#include<iostream>
#include<random>
#include <random>
#include <cstdlib>
#include <chrono>

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
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> distt(1,1000);
	std::uniform_int_distribution<int> distn(1,1000000000);
	int t=distt(gen);
	std::cout<<t;
	for(int i=0;i<t;i++) {
	    int n=distn(gen),m=distn(gen);
	    std::cout<<'\n'<<n<<' '<<m;
	}
}
