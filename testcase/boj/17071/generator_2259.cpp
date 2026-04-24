#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // With small probability, pick one of a few special edge cases
    if (rnd.next(0, 9) == 0) {
        vector<pair<int,int>> specials = {
            {0, 0}, {0, 500000}, {500000, 0}, {500000, 500000}
        };
        auto p = specials[rnd.next(0, (int)specials.size() - 1)];
        println(p.first, p.second);
        return 0;
    }

    // With some probability, force N == K
    if (rnd.next(0, 4) == 0) {
        int x = rnd.next(0, 500000);
        println(x, x);
        return 0;
    }

    // Hyperparameter: decide relation between N and K
    int mode = rnd.next(1, 3);
    int N, K;
    if (mode == 1) {
        // Ensure N <= K, but keep K not too far
        N = rnd.next(0, 300000);
        int maxK = min(N + 200000, 500000);
        K = rnd.next(N, maxK);
    } else if (mode == 2) {
        // Ensure N > K, but keep N not too far
        K = rnd.next(0, 300000);
        int minN = K + 1;
        int maxN = min(K + 200000, 500000);
        N = rnd.next(minN, maxN);
    } else {
        // Fully uniform
        N = rnd.next(0, 500000);
        K = rnd.next(0, 500000);
    }

    println(N, K);
    return 0;
}
