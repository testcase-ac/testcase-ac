#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_N = 2;
    const long long MAX_N = 4294967294LL;

    vector<long long> boundaries;
    long long x = 1;
    bool stanTurn = true;
    while (x <= MAX_N / (stanTurn ? 9 : 2)) {
        x *= stanTurn ? 9 : 2;
        boundaries.push_back(x);
        stanTurn = !stanTurn;
    }

    vector<long long> values;
    int cases = rnd.next(8, 24);

    while ((int)values.size() < cases) {
        int mode = rnd.next(0, 4);
        long long n;

        if (mode == 0) {
            n = rnd.next(MIN_N, 200LL);
        } else if (mode == 1) {
            long long b = rnd.any(boundaries);
            long long delta = rnd.next(-3, 3);
            n = b + delta;
        } else if (mode == 2) {
            long long b = rnd.any(boundaries);
            long long lo = max(MIN_N, b / 2);
            long long hi = min(MAX_N, b * 2);
            n = rnd.next(lo, hi);
        } else if (mode == 3) {
            n = rnd.next(1000000000LL, MAX_N);
        } else {
            n = rnd.any(vector<long long>{MIN_N, 9, 10, 18, 19, 162, 163, 324, MAX_N});
        }

        n = max(MIN_N, min(MAX_N, n));
        values.push_back(n);
    }

    shuffle(values.begin(), values.end());
    for (long long n : values) {
        println(n);
    }

    return 0;
}
