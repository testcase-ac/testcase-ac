//GPT 코드 기반으로 약간 수정한 코드
#include<bits/stdc++.h>
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

using ll=long long;

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
	random_device rd;
	mt19937_64 g(rd());
	
	uniform_int_distribution<int> dn(1,50);
	
	int n=dn(g),m=dn(g),l=dn(g);
	cout<<n<<' '<<m<<' '<<l<<'\n';
	
	ll lim=1000000000;
	vector<ll> h(n),w(m);
	
	ll s=0;
	for(int i=0;i<n;i++){
		ll r=uniform_int_distribution<ll>(1,min(lim/n*2,lim-s-(n-i-1)))(g);
		h[i]=r;
		s+=r;
	}
	
	s=0;
	for(int i=0;i<m;i++){
		ll r=uniform_int_distribution<ll>(1,min(lim/m*2,lim-s-(m-i-1)))(g);
		w[i]=r;
		s+=r;
	}
	
	for(int i=0;i<n;i++){
		cout<<h[i]<<(i+1<n?' ':'\n');
	}
	for(int i=0;i<m;i++){
		cout<<w[i]<<(i+1<m?' ':'\n');
	}
}
