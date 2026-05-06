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


int main(int argc, char* argv[]) {
    initSeed(argc, argv);
	random_device rd;
	mt19937 g(rd());
	uniform_int_distribution<int> dn(1,50),dm(1,50),dp(0,99);
	int n=dn(g),m=dm(g);
	cout<<n<<' '<<m<<'\n';
	int x=g()%n,y=g()%m;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			if(i==x&&j==y) {
				cout<<'*';
				continue;
			}
			int p=dp(g);
			if(p<25) cout<<'#';
			else cout<<'.';
		}
		cout<<'\n';
	}
}
