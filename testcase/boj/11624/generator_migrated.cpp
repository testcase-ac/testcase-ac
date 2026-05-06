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
    mt19937 rng(seedRng());
    int n = rng() % 100 + 1;
    int m = rng() % 100 + 1;
    int Q = rng() % 20 + 1;

    cout << n << " " << m << "\n";

    vector<string> pattern(n);
    for (int i = 0; i < n; i++) {
        string row;
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) row += '.';
            else row += (rng()%5<3 ? '.' : '#');
        }
        pattern[i] = row;
        cout << row << "\n";
    }

    cout << Q << "\n";
    for (int i = 0; i < Q; i++) {
        long long r,c;
        while(1) {
        r = rng() % 2000000001LL - 1000000000LL;
        c = rng() % 2000000001LL - 1000000000LL;
        int x=(r%n+n)%n,y=(c%m+m)%m;
        if(pattern[x][y]=='.'&&r&&c) break;
        }

        cout << r << " " << c << "\n";
    }
}
