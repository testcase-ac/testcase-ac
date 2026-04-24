#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of rides
    int M = rnd.next(1, 10);

    // Hyper-parameter for number of children
    long long N;
    if (rnd.next(0, 1)) {
        // Small N: N <= M
        N = rnd.next(1, M);
    } else {
        // Larger N: up to M + [1..20]
        int extra = rnd.next(1, 20);
        int hiN = M + extra;
        N = rnd.next(M + 1, hiN);
    }

    // Hyper-parameter for ride durations
    bool shortTimes = rnd.next(0, 1);
    vector<int> t(M);
    for (int i = 0; i < M; i++) {
        if (shortTimes) {
            // Mostly fast rides
            t[i] = rnd.next(1, 5);
        } else {
            // General range
            t[i] = rnd.next(1, 30);
        }
    }

    // Output
    println(N, M);
    println(t);

    return 0;
}
