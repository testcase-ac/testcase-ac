#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    int K = rnd.next(1, 10);

    // Hyper-parameters
    // Max absolute initial value
    int64_t maxInit = rnd.next(0, 20);
    // Max absolute update delta
    int64_t maxD = rnd.next(0, 10);
    // Probability to pick full-range operations
    double fullP = rnd.next();

    // Output header
    println(N, M, K);

    // Initial array
    for (int i = 0; i < N; i++) {
        int64_t v = rnd.next(-maxInit, maxInit);
        println(v);
    }

    // Prepare operation types and shuffle
    vector<int> ops;
    ops.reserve(M + K);
    for (int i = 0; i < M; i++) ops.push_back(1);
    for (int i = 0; i < K; i++) ops.push_back(2);
    shuffle(ops.begin(), ops.end());

    // Generate operations
    for (int t : ops) {
        int l, r;
        if (rnd.next() < fullP) {
            l = 1;
            r = N;
        } else {
            l = rnd.next(1, N);
            r = rnd.next(l, N);
        }
        if (t == 1) {
            // update
            int64_t d = rnd.next(-maxD, maxD);
            println(1, l, r, d);
        } else {
            // query
            println(2, l, r);
        }
    }

    return 0;
}
