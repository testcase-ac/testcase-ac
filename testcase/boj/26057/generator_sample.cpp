#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_V = 1000000000LL;
    int mode = rnd.next(0, 5);

    long long t;
    long long diff;

    if (mode == 0) {
        t = rnd.next(1LL, 12LL);
        diff = rnd.next(1LL, t);
    } else if (mode == 1) {
        t = rnd.next(1LL, 30LL);
        diff = 1;
    } else if (mode == 2) {
        t = rnd.next(1LL, 30LL);
        diff = t;
    } else if (mode == 3) {
        t = rnd.next(400000000LL, MAX_V);
        long long minDiff = max(1LL, 2 * t - MAX_V);
        long long maxDiff = min(t, minDiff + 2000);
        diff = rnd.next(minDiff, maxDiff);
    } else if (mode == 4) {
        t = rnd.next(1LL, MAX_V);
        long long minDiff = max(1LL, 2 * t - MAX_V);
        diff = rnd.next(minDiff, t);
    } else {
        vector<pair<long long, long long>> cases = {
            {1, 1},
            {2, 1},
            {500000000LL, 1},
            {500000001LL, 2},
            {1000000000LL, 1000000000LL},
        };
        auto chosen = rnd.any(cases);
        t = chosen.first;
        diff = chosen.second;
    }

    long long l = 2 * t - diff;

    println(l);
    println(t);
    return 0;
}
