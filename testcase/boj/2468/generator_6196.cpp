#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size N between small and medium for hand-verification
    int N = rnd.next(2, 15);
    println(N);

    // Prepare empty grid
    vector<vector<int>> a(N, vector<int>(N, 0));

    // Choose a pattern to expose different edge cases
    int pattern = rnd.next(0, 5);
    switch (pattern) {
        // 0: Uniform random heights up to a random max
        case 0: {
            int maxH = rnd.next(1, 100);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    a[i][j] = rnd.next(1, maxH);
            break;
        }
        // 1: All cells equal
        case 1: {
            int h = rnd.next(1, 100);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    a[i][j] = h;
            break;
        }
        // 2: Gradient (increasing with i+j)
        case 2: {
            int start = rnd.next(1, 50);
            int inc   = rnd.next(0, 5);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    a[i][j] = min(100, start + inc * (i + j));
            break;
        }
        // 3: Checkerboard of two heights
        case 3: {
            int h1 = rnd.next(1, 100);
            int h2 = rnd.next(1, 100);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    a[i][j] = ((i + j) % 2 == 0 ? h1 : h2);
            break;
        }
        // 4: Single rectangular blob of high height, rest low
        case 4: {
            int lowH = rnd.next(1, 50);
            int highH = rnd.next(lowH + 1, 100);
            int w = rnd.next(1, N);
            int h = rnd.next(1, N);
            int x0 = rnd.next(0, N - w);
            int y0 = rnd.next(0, N - h);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (i >= x0 && i < x0 + w && j >= y0 && j < y0 + h)
                        a[i][j] = highH;
                    else
                        a[i][j] = lowH;
                }
            }
            break;
        }
        // 5: Base height with random peaks
        case 5: {
            int base = rnd.next(1, 50);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    a[i][j] = base;
            int peaks = rnd.next(1, min(5, N * N));
            for (int t = 0; t < peaks; t++) {
                int i = rnd.next(0, N - 1);
                int j = rnd.next(0, N - 1);
                int ph = rnd.next(base + 1, 100);
                a[i][j] = ph;
            }
            break;
        }
    }

    // Output the grid
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }

    return 0;
}
