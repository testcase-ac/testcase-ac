#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose N from {1,2,3,4,5}
    vector<int> candN = {1, 2, 3, 4, 5};
    int N = rnd.any(candN);
    // Hyper-parameter: maximum sweetness
    int maxC = rnd.next(1, 20);
    // Choose a pattern for diversity
    int pattern = rnd.next(0, 4);
    vector<vector<int>> C(N, vector<int>(N));
    if (pattern == 0) {
        // Uniform random
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                C[i][j] = rnd.next(1, maxC);
    } else if (pattern == 1) {
        // Increasing mod maxC
        int cnt = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                C[i][j] = 1 + (cnt++ % maxC);
    } else if (pattern == 2) {
        // Checkerboard high/low
        int halfMax = max(1, maxC/2);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                if ((i + j) % 2 == 0) C[i][j] = maxC;
                else C[i][j] = rnd.next(1, halfMax);
            }
    } else if (pattern == 3) {
        // One high spike, others lower
        int halfMax = max(1, maxC/2);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                C[i][j] = rnd.next(1, halfMax);
        if (N > 0) {
            int x = rnd.next(0, N-1);
            int y = rnd.next(0, N-1);
            C[x][y] = maxC;
        }
    } else {
        // Row gradient with slight jitter
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                if (N == 1) {
                    C[i][j] = rnd.next(1, maxC);
                } else {
                    int base = 1 + (maxC - 1) * i / (N - 1);
                    int jitter = rnd.next(0, 1);
                    C[i][j] = min(maxC, base + jitter);
                }
            }
    }
    // Output
    println(N);
    for (int i = 0; i < N; i++)
        println(C[i]);
    return 0;
}
