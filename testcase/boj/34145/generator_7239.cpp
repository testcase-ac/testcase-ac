#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions N, M in [2,10], biased toward smaller
    int N = rnd.wnext(9, -2) + 2;
    int M = rnd.wnext(9, -2) + 2;
    // Number of queries Q in [0,8], biased small
    int Q = rnd.wnext(9, -2);

    println(N, M, Q);
    const string letters = "EWFA";
    // Initial grid
    for (int i = 0; i < N; i++) {
        string row;
        row.reserve(M);
        for (int j = 0; j < M; j++) {
            row += rnd.any(letters);
        }
        println(row);
    }
    // Generate queries with diverse rectangle shapes
    for (int qi = 0; qi < Q; qi++) {
        int t = rnd.next(1, 2);
        int shape = rnd.next(0, 3);
        int r1, r2, c1, c2;
        if (shape == 0) {
            // single cell
            r1 = r2 = rnd.next(1, N);
            c1 = c2 = rnd.next(1, M);
        } else if (shape == 1) {
            // full row
            int r = rnd.next(1, N);
            r1 = r2 = r;
            c1 = 1; c2 = M;
        } else if (shape == 2) {
            // full column
            int c = rnd.next(1, M);
            c1 = c2 = c;
            r1 = 1; r2 = N;
        } else {
            // general rectangle
            r1 = rnd.next(1, N);
            r2 = rnd.next(r1, N);
            c1 = rnd.next(1, M);
            c2 = rnd.next(c1, M);
        }
        println(t, r1, c1, r2, c2);
    }
    return 0;
}
