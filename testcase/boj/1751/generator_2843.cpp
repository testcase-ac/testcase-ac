#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small dimensions for hand-checkability
    int R = rnd.next(1, 8);
    int C = rnd.next(1, 8);
    int maxK = min(R, C);

    // Choose the size of the largest square-killer to embed
    int K = rnd.next(1, maxK);

    // Initialize matrix with random bits
    vector<string> a(R, string(C, '0'));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            a[i][j] = char('0' + rnd.next(0, 1));
        }
    }

    // Random position to embed a KxK symmetric square
    int r0 = rnd.next(0, R - K);
    int c0 = rnd.next(0, C - K);

    // Overwrite that submatrix to be 180-degree rotationally symmetric
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            int ii = K - 1 - i;
            int jj = K - 1 - j;
            // assign each pair once
            if (i < ii || (i == ii && j <= jj)) {
                char bit = char('0' + rnd.next(0, 1));
                a[r0 + i][c0 + j] = bit;
                a[r0 + ii][c0 + jj] = bit;
            }
        }
    }

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        printf("%s\n", a[i].c_str());
    }
    return 0;
}
