#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-check
    int N = rnd.next(2, 10);
    int R = rnd.next(1, N);
    int C = rnd.next(1, N);

    // Prepare the matrix
    vector<vector<int>> a(N, vector<int>(N));

    // Hyper-parameter: choose a pattern type for diversity
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // Fully random values
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = rnd.next(1, 100);
    } else if (pattern == 1) {
        // Globally increasing grid with slight noise
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int base = i * N + j;
                a[i][j] = base + rnd.next(1, 5);
            }
        }
    } else if (pattern == 2) {
        // Globally decreasing grid with slight noise
        int big = N * N * 10;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int idx = i * N + j;
                a[i][j] = big - idx - rnd.next(0, 5);
                if (a[i][j] < 1) a[i][j] = 1;
            }
        }
    } else {
        // Plateau-ish: row-based or column-based bands
        bool byRow = rnd.next(0, 1);
        if (byRow) {
            vector<int> base(N);
            for (int i = 0; i < N; i++)
                base[i] = rnd.next(1, 100);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    a[i][j] = base[i] + rnd.next(0, 10);
        } else {
            vector<int> base(N);
            for (int j = 0; j < N; j++)
                base[j] = rnd.next(1, 100);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    a[i][j] = base[j] + rnd.next(0, 10);
        }
    }

    // Output in the required format
    println(N);
    println(R, C);
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }

    return 0;
}
