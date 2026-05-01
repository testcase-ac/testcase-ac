#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: skewed low or high
    int skew = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int N = rnd.wnext(29, skew) + 2;  // N in [2,30]

    // Hyper-parameter for maximum initial cell value
    int maxCell;
    if (rnd.next(0,9) == 0) {
        // rare large values
        maxCell = rnd.next(200, 1000);
    } else {
        int t = rnd.any(vector<int>{-1, 0, 1});
        maxCell = rnd.wnext(10, t);  // typical 0..9 skewed
    }

    // Generate initial grid A
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rnd.next(maxCell + 1);
        }
    }

    // Output N and grid
    println(N);
    for (int i = 0; i < N; i++) {
        println(A[i]);
    }

    // Generate N operations
    for (int k = 0; k < N; k++) {
        int i, j;
        double r = rnd.next();
        if (r < 0.2) {
            // pick row at edge, col random
            i = rnd.any(vector<int>{1, N});
            j = rnd.next(1, N);
        } else if (r < 0.4) {
            // pick col at edge, row random
            j = rnd.any(vector<int>{1, N});
            i = rnd.next(1, N);
        } else {
            // fully random
            i = rnd.next(1, N);
            j = rnd.next(1, N);
        }
        char op;
        // cannot decrease if zero
        if (A[i-1][j-1] == 0) {
            op = 'U';
        } else {
            op = (rnd.next() < 0.5 ? 'U' : 'D');
        }
        // apply update
        if (op == 'U') A[i-1][j-1]++;
        else A[i-1][j-1]--;
        // output operation
        printf("%c %d %d\n", op, i, j);
    }

    return 0;
}
