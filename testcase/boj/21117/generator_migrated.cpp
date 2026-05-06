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
	int n=g()%21+1; //n>=22이면 testcase.ac에서 짤림
	cout<<n<<'\n';
	for(int i=0;i<n*2;i++) {
	    for(int j=0;j<n;j++) cout<<g()%2;
	    cout<<'\n';
	}
}
