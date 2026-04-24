#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sequence length and modulus
    int N = rnd.next(1, 10);
    int K = rnd.next(2, 20);

    // Hyper-parameters for A_i bounds
    int tmp = rnd.next(1, 10);
    int lowBound = rnd.next(1, tmp);
    int highBound = rnd.next(lowBound, lowBound + rnd.next(0, 20));

    // Generate sequence
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(lowBound, highBound);
    }

    // Number of queries
    int maxQ = N * (N + 1) / 2;
    int M = rnd.next(1, min(10, maxQ));

    // Precompute sizes for query-length hyper-parameters
    int maxSmall = max(1, N / 3);
    int maxLarge = maxSmall + (N - maxSmall) / 2;

    // Generate queries of varying spans
    vector<pair<int,int>> queries;
    for (int i = 0; i < M; i++) {
        int type = rnd.next(0, 3);
        int l, r;
        if (type == 0) {
            // full range
            l = 1; r = N;
        } else if (type == 1) {
            // small range
            int len = rnd.next(1, maxSmall);
            l = rnd.next(1, N - len + 1);
            r = l + len - 1;
        } else if (type == 2 && maxLarge >= maxSmall + 1) {
            // medium range
            int len = rnd.next(maxSmall + 1, maxLarge);
            l = rnd.next(1, N - len + 1);
            r = l + len - 1;
        } else if (type == 3 && maxLarge + 1 <= N) {
            // large range
            int len = rnd.next(maxLarge + 1, N);
            l = rnd.next(1, N - len + 1);
            r = l + len - 1;
        } else {
            // fallback random
            l = rnd.next(1, N);
            r = rnd.next(l, N);
        }
        queries.emplace_back(l, r);
    }

    // Output in problem format
    println(N, K);
    println(A);
    println(M);
    for (auto &qr : queries) {
        println(qr.first, qr.second);
    }

    return 0;
}
