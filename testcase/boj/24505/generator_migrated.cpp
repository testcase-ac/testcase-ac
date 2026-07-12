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
	mt19937_64 g(rd());
    uniform_int_distribution<int> T(1,2);
	uniform_int_distribution<int> r(1,100000);
    uniform_int_distribution<int> R(1,100);
    int t=T(g);
    int n;
    if(t==1) n=r(g);
    else n=R(g);
	cout<<n<<'\n';
	vector<int> v(n);
	iota(v.begin(),v.end(),1);
	shuffle(v.begin(),v.end(),g);
	for(int i=0;i<n;i++) cout<<v[i]<<(i+1==n?'\n':' ');
}
