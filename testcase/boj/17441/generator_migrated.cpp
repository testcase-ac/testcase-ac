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
	mt19937_64 r(seedRng());
	uniform_int_distribution<int> dn(3,100);
	uniform_int_distribution<int> dr(100,10000);
	uniform_real_distribution<long double> da(0,2*acos(-1));
	
	int n=dn(r);
	cout<<n<<'\n';
	
	vector<pair<long double,long double>> v;
	for(int i=0;i<n;i++){
		long double ang=da(r);
		long double rad=dr(r);
		v.push_back({ang,rad});
	}
	sort(v.begin(),v.end());
	
	for(int i=0;i<n;i++){
		long double x=v[i].second*cos(v[i].first);
		long double y=v[i].second*sin(v[i].first);
		cout<<(ll)x<<" "<<(ll)y<<'\n';
	}
}
