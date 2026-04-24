#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions: even N, M between 2 and 10
    int N = rnd.next(1, 5) * 2;
    int M = rnd.next(1, 5) * 2;
    // Number of operations
    int R = rnd.next(1, 10);

    // Choose a maximum value hyper-parameter, including the extreme case all ones
    vector<int> maxChoices = {2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 100000000};
    int maxV = rnd.any(maxChoices);

    // Generate the matrix A
    vector<vector<int>> A(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = rnd.next(1, maxV);
        }
    }

    // Generate operation sequence with a chance to include each op type at least once
    vector<int> ops(R);
    if (R >= 6 && rnd.next(0, 9) < 3) {
        vector<int> all = {1, 2, 3, 4, 5, 6};
        shuffle(all.begin(), all.end());
        // First 6 are a permutation of 1..6
        for (int i = 0; i < 6; i++) ops[i] = all[i];
        // Remaining are random
        for (int i = 6; i < R; i++) ops[i] = rnd.next(1, 6);
    } else {
        for (int i = 0; i < R; i++) {
            ops[i] = rnd.next(1, 6);
        }
    }

    // Output
    println(N, M, R);
    for (int i = 0; i < N; i++) {
        println(A[i]);
    }
    println(ops);

    return 0;
}
