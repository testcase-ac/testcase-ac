#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N but mix perfect squares and non-squares
    vector<int> squares = {1, 4, 9};
    vector<int> nonsq = {2, 3, 5, 6, 7, 8, 10};
    int N;
    if (rnd.next() < 0.5) {
        N = rnd.any(squares);
    } else {
        N = rnd.any(nonsq);
    }

    // Compute block size K and blocks
    int K = floor(sqrt(N));
    if (K < 1) K = 1;
    int block_cnt = (N + K - 1) / K;
    vector<pair<int,int>> blocks;
    for (int i = 0; i < block_cnt; i++) {
        int l = i * K + 1;
        int r = min(N, (i + 1) * K);
        blocks.emplace_back(l, r);
    }

    // Number of days M
    int M = rnd.next(1, 20);

    // Output header
    println(N, M);

    // Generate each day's feeding
    for (int day = 0; day < M; day++) {
        double p = rnd.next();
        int S, A;
        // 20%: span multiple full blocks
        if (p < 0.2 && block_cnt >= 2) {
            int b1 = rnd.next(0, block_cnt - 2);
            int b2 = rnd.next(b1, block_cnt - 1);
            A = blocks[b1].first;
            S = blocks[b2].second - blocks[b1].first + 1;
        }
        // 30%: align to exactly one block
        else if (p < 0.5 && block_cnt >= 1) {
            int b = rnd.next(0, block_cnt - 1);
            A = blocks[b].first;
            S = blocks[b].second - blocks[b].first + 1;
        }
        // Otherwise random partial
        else {
            A = rnd.next(1, N);
            int maxS = N - A + 1;
            S = rnd.next(1, maxS);
        }
        // Print S and A
        println(S, A);
    }

    return 0;
}
