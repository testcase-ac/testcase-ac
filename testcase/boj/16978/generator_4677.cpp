#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checking
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);

    // Hyper-parameter for value distribution
    int maxVal = rnd.next(5, 20);
    int tVal = rnd.next(-2, 2);

    // Generate initial array A[1..N] with values in [1, maxVal]
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        if (tVal == 0) {
            A[i] = rnd.next(1, maxVal);
        } else {
            // rnd.wnext(maxVal, tVal) gives [0..maxVal-1], so +1 shifts to [1..maxVal]
            A[i] = rnd.wnext(maxVal, tVal) + 1;
        }
    }

    // Output N and initial array
    println(N);
    println(A);

    // Number of queries
    println(M);

    int updCount = 0;
    int queryCount = 0;
    for (int qi = 0; qi < M; qi++) {
        // Decide update (type 1) or query (type 2)
        bool isUpdate;
        if (qi == M - 1 && queryCount == 0) {
            // Ensure at least one type-2 query
            isUpdate = false;
        } else {
            isUpdate = (rnd.next(0, 1) == 1);
        }
        if (isUpdate) {
            // Type-1: update A[idx] = v
            int idx = rnd.next(1, N);
            int v;
            if (tVal == 0) {
                v = rnd.next(1, maxVal);
            } else {
                v = rnd.wnext(maxVal, tVal) + 1;
            }
            println(1, idx, v);
            updCount++;
        } else {
            // Type-2: query sum after k updates
            int l = rnd.next(1, N);
            int r = rnd.next(l, N);
            int k = rnd.next(0, updCount);
            println(2, k, l, r);
            queryCount++;
        }
    }

    return 0;
}
