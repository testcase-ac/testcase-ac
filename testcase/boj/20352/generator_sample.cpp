#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000000000LL;
    vector<long long> candidates;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        candidates.push_back(rnd.next(1, 1000));
    } else if (mode == 1) {
        long long x = rnd.next(1LL, 1000000000LL);
        candidates.push_back(x * x);
    } else if (mode == 2) {
        long long base = 1;
        int zeros = rnd.next(0, 18);
        for (int i = 0; i < zeros; ++i) base *= 10;
        long long delta = rnd.next(0, 999);
        if (rnd.next(0, 1) == 0) {
            candidates.push_back(max(1LL, base - delta));
        } else {
            candidates.push_back(min(LIMIT, base + delta));
        }
    } else if (mode == 3) {
        long long span = rnd.next(0, 1000000);
        candidates.push_back(LIMIT - span);
    } else if (mode == 4) {
        long long hi = rnd.next(1000000LL, LIMIT);
        long long lo = rnd.next(1LL, hi);
        candidates.push_back(rnd.next(lo, hi));
    } else {
        candidates = {1, 2, 3, 4, 64, 1234, LIMIT - 1, LIMIT};
    }

    println(rnd.any(candidates));
    return 0;
}
