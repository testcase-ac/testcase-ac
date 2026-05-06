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
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,100);
    uniform_int_distribution<int> disn(0,1000000001);
    uniform_int_distribution<int> dism(1,1001); // fixed by admin: originally (0, 1001)
    int t=dist(gen);
    cout<<t<<'\n';
    for(int i=0;i<t/2;i++) {
        t--;
        cout<<dism(gen)<<' '<<dism(gen)<<'\n';
    } while(t--) {
        cout<<disn(gen)<<' '<<disn(gen)<<'\n';
    }
}
