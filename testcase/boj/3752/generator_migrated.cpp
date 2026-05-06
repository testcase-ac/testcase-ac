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
	mt19937_64 g(rd());
	int t=g()%10+1;
	cout<<t<<'\n';
	while(t--){
		int m=5+g()%5;
		vector<int> a;
		for(int i=0;i<m;i++){
			int x=g()%2000000000+1;
			a.push_back(x);
		} set<int> s;
		for(int x:a){
			for(int d=1;d*d<=x;d++) {
				if(x%d==0){
					s.insert(d);
					s.insert(x/d);
				}
			}
		} if(s.size()>1000) {t++;continue;}
		cout<<s.size()<<'\n';
		for(int x:s) cout<<x<<" ";
		cout<<'\n';
	}
}
