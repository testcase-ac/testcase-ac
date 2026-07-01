#include <bits/stdc++.h>
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
	mt19937 rng(seedRng());
	uniform_int_distribution<int> xd(-1000,1000);
	uniform_int_distribution<int> yd(1,1000);
	int T=rand()%10+1;
	cout<<T<<'\n';
	for(int i=0;i<T;i++) {
		int x1=xd(rng),y1=yd(rng);
		int x2=xd(rng),y2=yd(rng);
		cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<'\n';
	}
}
