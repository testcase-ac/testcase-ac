#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small grid dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    int Q = rnd.next(1, 20);

    // Hyper-parameters for fish distribution
    int valueBreakpoint = rnd.next(50, 450);
    double highProb = rnd.next(0.0, 1.0);

    // Generate the fish grid
    vector<vector<int>> A(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (rnd.next() < highProb) {
                // Heavy cell
                A[i][j] = rnd.next(valueBreakpoint, 500);
            } else {
                // Light cell
                A[i][j] = rnd.next(0, valueBreakpoint);
            }
        }
    }

    // Output N, M, Q
    println(N, M, Q);
    // Output grid rows
    for (int i = 0; i < N; i++) {
        println(A[i]);
    }

    // Generate queries with varied regions
    for (int qi = 0; qi < Q; qi++) {
        double pick = rnd.next();
        int W, P;
        if (pick < 0.1) {
            // Near the top-left corner
            W = rnd.next(1, min(3, N));
            P = rnd.next(1, min(3, M));
        } else if (pick < 0.2) {
            // Near the bottom-right corner
            W = rnd.next(max(1, N - 2), N);
            P = rnd.next(max(1, M - 2), M);
        } else {
            // Anywhere
            W = rnd.next(1, N);
            P = rnd.next(1, M);
        }
        println(W, P);
    }

    return 0;
}
