#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: skewed small or large
    int weightN = rnd.next(-2, 2);
    int N = rnd.wnext(30, weightN) + 1;  // 1 <= N <= 30

    // Hyper-parameter for initial values: small or large max bound
    vector<int> maxOpts = {5, 10, 100, 1000, 1000000000};
    int maxA = rnd.any(maxOpts);

    // Generate initial sequence
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(1, maxA);
    }

    // Hyper-parameter for M: number of queries
    int weightM = rnd.next(-2, 2);
    int M = rnd.wnext(30, weightM) + 1;  // 1 <= M <= 30

    // Probability threshold for updates vs queries
    int probUpdate = rnd.next(0, 100);

    // Output
    println(N);
    println(A);
    println(M);
    for (int qi = 0; qi < M; qi++) {
        if (rnd.next(0, 99) < probUpdate) {
            // Type 1: update
            int pos = rnd.next(1, N);
            int x = rnd.next(1, maxA);
            println(1, pos, x);
        } else {
            // Type 2 or 3: query
            int l = rnd.next(1, N);
            int r = rnd.next(l, N);
            int type = rnd.next(2, 3);
            println(type, l, r);
        }
    }

    return 0;
}
