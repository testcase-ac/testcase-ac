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

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
	ios::sync_with_stdio(0);
	cin.tie(0);

	random_device rd;
	mt19937_64 r(rd());

	int n=r()%51+2;
	int k=r()%(n/2+1);

	ll g=r()%((ll)1e12-1)+2;

	vector<ll>a(n);

	for(int i=0;i<n-k;i++){
		ll x=r()%1000000+1;
		if(g*x>1e18)x=1;
		a[i]=g*x;
	}

	for(int i=n-k;i<n;i++){
		ll x=r()%((ll)1e18-1)+1;
		if(x%g==0)x++;
		a[i]=x;
	}

	shuffle(a.begin(),a.end(),r);

	cout<<n<<' '<<k<<'\n';
	for(int i=0;i<n;i++){
		cout<<a[i];
		if(i+1<n)cout<<' ';
	}
	cout<<'\n';
}
