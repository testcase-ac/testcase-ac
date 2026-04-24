/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N biased towards larger values in [1,10]
    int N = rnd.wnext(10, 2) + 1;
    // Maximum queries we'll emit (at most 20, but ≤ N*N)
    int maxQ = min(20, N * N);
    // Choose M biased towards smaller values in [1, maxQ]
    int M = rnd.wnext(maxQ, -2) + 1;

    // Generate the matrix values (1 to 1000)
    vector<vector<int>> a(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rnd.next(1, 1000);
        }
    }

    // Output header
    println(N, M);
    // Output matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j) printf(" ");
            printf("%d", a[i][j]);
        }
        printf("\n");
    }
    // Generate and output queries
    for (int i = 0; i < M; i++) {
        int x1 = rnd.next(1, N);
        int x2 = rnd.next(x1, N);
        int y1 = rnd.next(1, N);
        int y2 = rnd.next(y1, N);
        println(x1, y1, x2, y2);
    }

    return 0;
}
