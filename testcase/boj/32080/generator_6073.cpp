#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N small for hand-checking, but variable
    int N = rnd.next(1, 10);
    vector<int> C;
    int mode = rnd.next(0, 2); // 0: impossible, 1-2: feasible

    if (mode == 0) {
        // Generate a simple impossible pattern: full descending
        C.resize(2 * N);
        for (int i = 0; i < 2 * N; i++) {
            C[i] = 2 * N - i;
        }
        // Special case: N=1, ensure impossible [2,1]
        if (N == 1) {
            C = {2, 1};
        }
    } else {
        // Feasible: construct random A and B, then simulate merge
        vector<int> P(2 * N);
        iota(P.begin(), P.end(), 1);
        shuffle(P.begin(), P.end());

        vector<int> A(P.begin(), P.begin() + N);
        vector<int> B(P.begin() + N, P.end());

        // Hyper-parameter: sometimes sort A or B to catch wrong assumptions
        if (rnd.next(0, 1)) {
            sort(A.begin(), A.end());
        }
        if (rnd.next(0, 1)) {
            sort(B.begin(), B.end());
        }

        C.clear();
        C.reserve(2 * N);
        int i = 0, j = 0;
        // Simulate the given merge routine
        while (i < N && j < N) {
            if (A[i] < B[j]) {
                C.push_back(A[i++]);
            } else {
                C.push_back(B[j++]);
            }
        }
        while (i < N) {
            C.push_back(A[i++]);
        }
        while (j < N) {
            C.push_back(B[j++]);
        }
    }

    // Output
    println(N);
    println(C);

    return 0;
}
