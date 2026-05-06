//GPT 코드
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

using ll=long long;

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
	random_device rd;
	mt19937_64 g(rd());
	
	uniform_int_distribution<int> dn(1,30);
	int n=dn(g);
	
	int mx=n*(n-1)/2;
	uniform_int_distribution<int> dm(0,mx);
	int m=dm(g);
	
	uniform_int_distribution<ll> dk(1,1000000000000000000LL);
	ll k=dk(g);
	
	vector<pair<int,int>> e;
	set<pair<int,int>> s;
	
	uniform_int_distribution<int> dv(1,n);
	while(s.size()<m) {
		int a=dv(g),b=dv(g);
		if(a==b) continue;
		if(a>b) swap(a,b);
		if(s.insert({a,b}).second) e.push_back({a,b});
	}
	
	cout<<n<<' '<<m<<' '<<k<<'\n';
	for(auto &p:e) cout<<p.first<<' '<<p.second<<'\n';
}
