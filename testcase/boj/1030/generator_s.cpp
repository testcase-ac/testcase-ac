#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long ipow(long long a, int e) {
    long long res = 1;
    while (e--) res *= a;
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // S and N are sampled uniformly.
    // Coordinates are uniform only in [0, N^S - 1], not globally.
    int S = rnd.next(0, 10);
    int N = rnd.next(3, 8);

    vector<int> candidates;
    for (int K = 1; K <= N - 2; K++) {
        if ((N - K) % 2 == 0) candidates.push_back(K);
    }

    // K is uniform among valid values.
    int K = candidates[rnd.next(0, (int)candidates.size() - 1)];

    long long limit = ipow(N, S) - 1;

    // Small coordinates are frequent because small S is sampled as often as large S.
    long long R1 = rnd.next(0LL, limit);
    long long C1 = rnd.next(0LL, limit);

    // Window size is at most 50x50, clipped by the boundary.
    long long R2 = rnd.next(R1, min(limit, R1 + 49));
    long long C2 = rnd.next(C1, min(limit, C1 + 49));

    println(S, N, K, R1, R2, C1, C2);

    return 0;
}