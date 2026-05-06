//GPT가 짠 코드
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

	int w=uniform_int_distribution<int>(1,1000000000)(rng);

	int c,h;
	while(1){
		c=uniform_int_distribution<int>(0,1000)(rng);
		int k=c+1;
		int mx=1000000000/k;
		if(mx==0) continue;
		h=uniform_int_distribution<int>(1,mx)(rng)*k;
		break;
	}

	int f=uniform_int_distribution<int>(0,w)(rng);
	int mx=max(f,w-f);

	int x1=uniform_int_distribution<int>(0,mx-1)(rng);
	int x2=uniform_int_distribution<int>(x1+1,mx)(rng);

	int hh=h/(c+1);
	int y1=uniform_int_distribution<int>(0,hh-1)(rng);
	int y2=uniform_int_distribution<int>(y1+1,hh)(rng);

	cout<<w<<' '<<h<<' '<<f<<' '<<c<<' '
	    <<x1<<' '<<y1<<' '<<x2<<' '<<y2<<'\n';
}
