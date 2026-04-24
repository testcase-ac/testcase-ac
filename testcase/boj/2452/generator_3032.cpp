#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size
    int M = rnd.next(2, 10);
    int N = rnd.next(2, 10);

    // Prepare grid
    vector<vector<int>> a(M, vector<int>(N, 0));

    // Choose a pattern type for diversity
    // 0: random Bernoulli with various densities
    // 1: all zeros
    // 2: all ones
    // 3: single rectangular blob of ones
    // 4: checkerboard
    int pattern = rnd.next(0, 4);

    if (pattern == 0) {
        // Random Bernoulli with one of a few density choices
        double p;
        int dt = rnd.next(0, 3);
        if (dt == 0) p = 0.2;
        else if (dt == 1) p = 0.5;
        else if (dt == 2) p = 0.8;
        else p = rnd.next();  // fallback
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = (rnd.next() < p ? 1 : 0);
            }
        }
    }
    else if (pattern == 1) {
        // All zeros (white)
        // already initialized
    }
    else if (pattern == 2) {
        // All ones (black)
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = 1;
    }
    else if (pattern == 3) {
        // Single rectangular blob of ones on zeros
        int r1 = rnd.next(0, M-1);
        int c1 = rnd.next(0, N-1);
        int r2 = rnd.next(r1, M-1);
        int c2 = rnd.next(c1, N-1);
        // fill zeros first
        // already zeros
        for (int i = r1; i <= r2; i++)
            for (int j = c1; j <= c2; j++)
                a[i][j] = 1;
    }
    else {
        // Checkerboard
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = (i + j) % 2;
    }

    // Output
    println(M, N);
    for (int i = 0; i < M; i++) {
        println(a[i]);
    }
    return 0;
}
