#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_K = 2;
    const long long MAX_K = 1000000000000000000LL;
    const long long MOD = 1000003;

    vector<long long> candidates;
    auto add = [&](long long value) {
        if (MIN_K <= value && value <= MAX_K) candidates.push_back(value);
    };

    int mode = rnd.next(8);
    if (mode == 0) {
        add(rnd.next(2LL, 9LL));
    } else if (mode == 1) {
        long long center = rnd.any(vector<long long>{4, 10, 30});
        add(center + rnd.next(-3LL, 3LL));
    } else if (mode == 2) {
        long long center = 100000;
        add(center + rnd.next(-500LL, 500LL));
    } else if (mode == 3) {
        add(rnd.next(31LL, 1000000LL));
    } else if (mode == 4) {
        long long block = rnd.next(1LL, 1000000LL);
        add(block * MOD + rnd.next(-8LL, 8LL));
    } else if (mode == 5) {
        long long block = rnd.next(1LL, 1000000LL);
        add(block * (MOD - 1) + rnd.next(-8LL, 8LL));
    } else if (mode == 6) {
        long long base = MAX_K - rnd.next(0LL, 1000000LL);
        add(base);
    } else {
        long long hi = rnd.next(1000000000000LL, MAX_K);
        long long lo = max(MIN_K, hi - rnd.next(0LL, 1000000000000LL));
        add(rnd.next(lo, hi));
    }

    if (candidates.empty()) add(rnd.next(MIN_K, MAX_K));
    println(rnd.any(candidates));
    return 0;
}
