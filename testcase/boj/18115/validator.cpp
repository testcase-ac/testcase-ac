#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // 2. Read A[0..N-1]
    vector<int> A = inf.readInts(N, 1, 3, "A_i");
    inf.readEoln();

    // 3. Constraint: A[N-1] == 1
    ensuref(A[N-1] == 1, "A[N] (the last operation) must be 1, but got %d", A[N-1]);

    // 4. Constraint: For i in 0..N-2, if A[i] in {2,3}, then i <= N-2 (i.e., at least 2 cards left)
    //    (A[N-1] is always 1, so only check i in 0..N-2)
    for (int i = 0; i < N-1; ++i) {
        if (A[i] == 2 || A[i] == 3) {
            // At this step, there must be at least 2 cards in hand
            // At step i, cards in hand = N - i
            ensuref(N - i >= 2, "Operation %d at index %d requires at least 2 cards in hand, but only %d left", A[i], i+1, N-i);
        }
    }

    inf.readEof();
}
