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
	int t=uniform_int_distribution<int>(1,10)(g);
	cout<<t<<'\n';
	for(int i=0;i<t;i++) {
		int n=uniform_int_distribution<int>(1,100000)(g);
		int k=uniform_int_distribution<int>(1,min(100,n))(g);
		cout<<n<<' '<<k<<'\n';
		set<int> s;
		while(s.size()<k) s.insert(uniform_int_distribution<int>(1,n)(g));
		vector<int> a(s.begin(),s.end());
		for(int j=0;j<k;j++) cout<<a[j]<<(j+1<k?' ':'\n');
		s.clear();
		while(s.size()<k) s.insert(uniform_int_distribution<int>(1,n)(g));
		vector<int> b(s.begin(),s.end());
		for(int j=0;j<k;j++) cout<<b[j]<<(j+1<k?' ':'\n');
	}
}
