#include "testlib.h"
#include <vector>
using namespace std;

int wrap10(int x) {
    return (x % 10 + 10) % 10;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int N = 6;
    vector<vector<int>> a(N, vector<int>(N));

    // Choose one of several patterns to expose different wrong-solution pitfalls
    // 0: fully uniform random
    // 1: row-biased values
    // 2: column-biased values
    // 3: diagonal-biased values
    // 4: checkerboard high/low
    // 5: constant grid
    int pattern = rnd.next(0, 5);

    if (pattern == 0) {
        // Fully random
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = rnd.next(0, 9);

    } else if (pattern == 1) {
        // Row bias
        vector<int> rb(N);
        for (int i = 0; i < N; i++)
            rb[i] = rnd.next(-9, 9);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = wrap10(rnd.next(0, 9) + rb[i]);

    } else if (pattern == 2) {
        // Column bias
        vector<int> cb(N);
        for (int j = 0; j < N; j++)
            cb[j] = rnd.next(-9, 9);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = wrap10(rnd.next(0, 9) + cb[j]);

    } else if (pattern == 3) {
        // Diagonal bias
        int d1 = rnd.next(-9, 9), d2 = rnd.next(-9, 9);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int v = rnd.next(0, 9);
                if (i == j) v += d1;
                if (i + j == N - 1) v += d2;
                a[i][j] = wrap10(v);
            }
        }

    } else if (pattern == 4) {
        // Checkerboard: high on even cells, low on odd cells
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if ((i + j) % 2 == 0)
                    a[i][j] = rnd.next(5, 9);
                else
                    a[i][j] = rnd.next(0, 4);
            }
        }

    } else {
        // Constant grid
        int c = rnd.next(0, 9);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = c;
    }

    // Output the 6x6 grid
    for (int i = 0; i < N; i++)
        println(a[i]);

    return 0;
}
