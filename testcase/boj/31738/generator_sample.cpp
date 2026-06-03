#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

long long randomN(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

int randomM(int lo, int hi) {
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000000000LL;
    const int MAX_M = 10000000;

    long long n;
    int m;

    int mode = rnd.next(0, 8);
    if (mode == 0) {
        vector<pair<long long, int>> edges = {
            {2, 2},
            {2, MAX_M},
            {MAX_N, 2},
            {MAX_N, MAX_M},
        };
        auto choice = rnd.any(edges);
        n = choice.first;
        m = choice.second;
    } else if (mode == 1) {
        m = randomM(3, 30);
        n = randomN(2, m - 1);
    } else if (mode == 2) {
        m = randomM(31, 1000);
        n = randomN(max(2, m - 25), m - 1);
    } else if (mode == 3) {
        n = randomN(2, 200);
        m = randomM(2, min<long long>(MAX_M, n));
    } else if (mode == 4) {
        m = randomM(2, MAX_M);
        n = randomN(m, min(MAX_N, (long long)m + 200));
    } else if (mode == 5) {
        m = randomM(MAX_M - 1000, MAX_M);
        n = randomN(2, min(100000LL, (long long)m - 1));
    } else if (mode == 6) {
        m = randomM(2, MAX_M);
        n = randomN(MAX_N - 1000000, MAX_N);
    } else {
        m = randomM(2, MAX_M);
        n = randomN(2, MAX_N);
    }

    println(n, m);
    return 0;
}
