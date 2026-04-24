#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for M: sometimes small, sometimes larger
    int M;
    if (rnd.next(4) == 0)
        M = rnd.next(1, 3);
    else
        M = rnd.next(5, 20);

    // Hyper-parameter for R: sometimes divisor of 720, else random
    vector<int> divs;
    for (int d = 1; d < 720; ++d)
        if (720 % d == 0)
            divs.push_back(d);
    int R;
    if (rnd.next(4) == 0)
        R = rnd.any(divs);
    else
        R = rnd.next(1, 719);

    // Hyper-parameter for number of clocks K
    int K;
    if (rnd.next(4) == 0)
        K = M;  // worst-case many
    else
        K = rnd.next(1, min(M, 5));

    // Generate distinct initial offsets for each clock
    vector<int> pool(720);
    iota(pool.begin(), pool.end(), 0);
    shuffle(pool.begin(), pool.end());
    vector<int> init(pool.begin(), pool.begin() + K);

    // Generate sequence of picks with some clustering
    vector<int> pick(M);
    if (M > 0) {
        pick[0] = rnd.next(0, K - 1);
        double sameProb = rnd.next(0.0, 1.0);
        for (int i = 1; i < M; ++i) {
            if (rnd.next() < sameProb)
                pick[i] = pick[i-1];
            else
                pick[i] = rnd.next(0, K - 1);
        }
    }

    // Compute recorded times
    vector<int> rec(M);
    for (int i = 0; i < M; ++i) {
        long long val = init[pick[i]] + 1LL * i * R;
        rec[i] = int((val % 720 + 720) % 720);
    }

    // Output
    println(M);
    for (int i = 0; i < M; ++i) {
        int hh = rec[i] / 60;
        int mm = rec[i] % 60;
        if (hh == 0) hh = 12;
        printf("%02d:%02d\n", hh, mm);
    }
    return 0;
}
