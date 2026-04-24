#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size
    int N = rnd.next(1, 10);
    int Q = rnd.next(1, 20);

    // Generate heights A with diversity: random, sorted, or reversed
    int mode = rnd.next(0, 2);
    int lo = rnd.next(1, 20);
    int hi = rnd.next(lo, 100);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(lo, hi);
    }
    if (mode == 1) {
        sort(A.begin(), A.end());
    } else if (mode == 2) {
        sort(A.begin(), A.end(), greater<int>());
    }

    // Output N and total operations Q
    println(N, Q);
    println(A);

    // Decide how many queries (1) and swaps (2)
    int X = rnd.next(1, Q);
    int Y = Q - X;
    vector<int> ops;
    ops.reserve(Q);
    for (int i = 0; i < X; i++) ops.push_back(1);
    for (int i = 0; i < Y; i++) ops.push_back(2);
    shuffle(ops.begin(), ops.end());

    // Generate operations
    for (int t : ops) {
        if (t == 1) {
            // Query: ask non-decreasing on [L, R]
            int L = rnd.next(1, N);
            int R = rnd.next(L, N);
            println(1, L, R);
        } else {
            // Swap: sometimes adjacent, sometimes random
            int L, R;
            if (N >= 2 && rnd.next(0, 1) == 0) {
                L = rnd.next(1, N - 1);
                R = L + 1;
            } else {
                L = rnd.next(1, N);
                R = rnd.next(L, N);
            }
            println(2, L, R);
        }
    }

    return 0;
}
