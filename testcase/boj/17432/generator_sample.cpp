#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long maxInversions(long long n) {
    return n * (n - 1) / 2;
}

long long biasedM(long long limit, int mode) {
    if (limit == 0) return 0;
    if (mode == 0) return rnd.next(0LL, min(20LL, limit));
    if (mode == 1) return limit - rnd.next(0LL, min(20LL, limit));
    if (mode == 2) return rnd.next(0LL, limit);

    long long center = limit / 2;
    long long spread = min(1000LL, limit);
    long long lo = max(0LL, center - spread);
    long long hi = min(limit, center + spread);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    vector<pair<int, long long>> cases;

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 7);
        int n;

        if (mode == 0) {
            n = 1;
        } else if (mode <= 3) {
            n = rnd.next(2, 12);
        } else if (mode <= 5) {
            n = rnd.next(13, 80);
        } else if (mode == 6) {
            n = rnd.next(1000, 5000);
        } else {
            n = rnd.next(90000, 100000);
        }

        long long limit = maxInversions(n);
        long long m = biasedM(limit, mode % 4);
        cases.push_back({n, m});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [n, m] : cases) {
        println(n, m);
    }

    return 0;
}
