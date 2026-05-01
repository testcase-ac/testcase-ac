#include "testlib.h"
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Random dimensions (small to medium for manual verification)
    int N = rnd.next(1, 20);
    int M = rnd.next(1, 20);
    vector<string> grid(N, string(M, '0'));

    // Diversity hyper-parameters
    int pattern = rnd.next(0, 6);   // choose a pattern type
    double density = rnd.next();    // base probability for random walls

    switch (pattern) {
        case 0: {
            // Uniform random walls
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    if (rnd.next() < density)
                        grid[i][j] = '1';
            break;
        }
        case 1: {
            // Diagonal dominant with some noise
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    if (i == j % N || rnd.next() < density * 0.3)
                        grid[i][j] = '1';
            break;
        }
        case 2: {
            // Horizontal stripes
            int stripeH = rnd.next(1, max(1, N / 3));
            for (int i = 0; i < N; i++) {
                bool fill = ((i / stripeH) % 2 == 0);
                for (int j = 0; j < M; j++)
                    grid[i][j] = fill ? '1' : '0';
            }
            // small random flips
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    if (rnd.next() < density * 0.2)
                        grid[i][j] = (grid[i][j] == '1' ? '0' : '1');
            break;
        }
        case 3: {
            // Vertical stripes
            int stripeW = rnd.next(1, max(1, M / 3));
            for (int j = 0; j < M; j++) {
                bool fill = ((j / stripeW) % 2 == 0);
                for (int i = 0; i < N; i++)
                    grid[i][j] = fill ? '1' : '0';
            }
            // small random flips
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    if (rnd.next() < density * 0.2)
                        grid[i][j] = (grid[i][j] == '1' ? '0' : '1');
            break;
        }
        case 4: {
            // Single cluster of walls
            // background sparse walls
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    if (rnd.next() < density * 0.1)
                        grid[i][j] = '1';
            int ci = rnd.next(0, N - 1), cj = rnd.next(0, M - 1);
            int hiRad = max(N, M) / 2;
            int rad = rnd.next(0, hiRad);  // can be zero for a single-cell cluster
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++) {
                    int di = i - ci, dj = j - cj;
                    if (di * di + dj * dj <= rad * rad)
                        grid[i][j] = '1';
                }
            break;
        }
        case 5: {
            // All open (no walls)
            // grid is already '0'
            break;
        }
        case 6: {
            // All walls
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    grid[i][j] = '1';
            break;
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        printf("%s\n", grid[i].c_str());

    return 0;
}
