#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions: allow some degenerate 1-row or 1-col cases
    bool lineCase = rnd.next() < 0.2;
    int N, M;
    if (lineCase) {
        if (rnd.next(0,1) == 0) {
            N = 1;
            M = rnd.next(1,6);
        } else {
            N = rnd.next(1,6);
            M = 1;
        }
    } else {
        N = rnd.next(1,6);
        M = rnd.next(1,6);
    }

    // Maximum stack height
    int Hmax = rnd.next(1,9);

    // Choose pattern for variability
    int pat = (Hmax >= 2 ? rnd.next(0,3) : rnd.next(0,1));
    vector<vector<int>> a(N, vector<int>(M));

    if (pat == 0) {
        // Fully random
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                a[i][j] = rnd.next(1, Hmax);
    } else if (pat == 1) {
        // Uniform grid
        int h = rnd.next(1, Hmax);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                a[i][j] = h;
    } else if (pat == 2) {
        // Row-wise constant
        vector<int> rowVal(N);
        for (int i = 0; i < N; i++)
            rowVal[i] = rnd.next(1, Hmax);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                a[i][j] = rowVal[i];
    } else {
        // Checkerboard high/low
        int v1 = rnd.next(1, Hmax), v2 = rnd.next(1, Hmax);
        while (v2 == v1) v2 = rnd.next(1, Hmax);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                a[i][j] = ((i + j) % 2 ? v1 : v2);
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        println(a[i]);

    return 0;
}
