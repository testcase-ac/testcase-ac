//GPT 코드
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

mt19937_64 rng;

ll rd(ll l,ll r){
	return uniform_int_distribution<ll>(l,r)(rng);
}

ll pw10(int k){
	ll r=1;
	while(k--)r*=10;
	return r;
}

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    rng.seed(seedRng());
	int T=rd(1,30);
	cout<<T<<'\n';

	for(int tc=0;tc<T;tc++){
		ll P,m;
		int k;

		while(1){
			P=rd(1,(ll)1e18);
			ll g=gcd(P,(ll)1e18);
			if(g<5)break;
		}

		m=rd(1,(ll)1e18);
		k=rd(1,18);

		ll lim=pw10(k)-1;
		ll v=rd(0,lim);

		string s=to_string(v);
		while((int)s.size()<k)s='0'+s;

		cout<<P<<' '<<m<<' '<<s<<'\n';
	}
}
