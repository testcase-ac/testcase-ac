#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
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
	random_device r;
	mt19937_64 g(r());
	uniform_int_distribution<int> d(4,1000000);
	int k=0;
	while(1) {
		int n=d(g);
		vector<int> v;
		bool ok=1;
		for(int i=2;i*i<=n;i++) {
			if(n%i==0) {
				if(i>1000000||n/i>1000000) {
					ok=0;
					break;
				} v.push_back(i);
				if(i!=n/i) v.push_back(n/i);
			}
		} if(ok&&v.size()<=50&&(k>10||v.size()>2)) {
			cout<<v.size()<<'\n';
			random_shuffle(v.begin(),v.end());
			for(int i=0;i<v.size()-1;i++) cout<<v[i]<<' ';
			cout<<v[v.size()-1];
			return 0;
		} if(v.size()==2) k++;
	}
}
