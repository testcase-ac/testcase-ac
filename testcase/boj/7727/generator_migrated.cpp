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

mt19937 rng;
string gen(int len) {
	string s;
	for(int i=0;i<len;i++) s+='a'+rng()%26;
	return s;
}
int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    rng.seed(seedRng());
	int len1=rng()%1000+1,len2=rng()%1000+1;
	string a=gen(len1), b=gen(len2);
	cout<<len1<<' '<<len2<<'\n'<<a<<'\n'<<b<<'\n';
}
