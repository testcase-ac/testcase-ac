#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 15);
    int Q = rnd.next(1, 15);

    // Generate operations with diverse range lengths and values
    vector<tuple<int,int,int>> ops;
    for (int i = 0; i < M; i++) {
        // Length biased towards small via wnext with t = -1
        int length = rnd.wnext(N, -1) + 1;
        int L = rnd.next(1, N - length + 1);
        int R = L + length - 1;
        int X = rnd.next(-10, 10);  // small positive/negative updates
        ops.emplace_back(L, R, X);
    }

    // Output N, M and operations
    println(N, M);
    for (auto &op : ops) {
        int L, R, X;
        tie(L, R, X) = op;
        println(L, R, X);
    }

    // Generate queries covering single ops, full range, and random
    println(Q);
    for (int i = 0; i < Q; i++) {
        int K = rnd.next(1, N);
        int S, T;
        if (i == 0) {
            // Single operation query
            S = rnd.next(1, M);
            T = S;
        } else if (i == 1) {
            // Full range query
            S = 1;
            T = M;
        } else {
            S = rnd.next(1, M);
            T = rnd.next(S, M);
        }
        println(K, S, T);
    }
    return 0;
}
