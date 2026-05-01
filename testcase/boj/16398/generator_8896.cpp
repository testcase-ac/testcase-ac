#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N so that total input stays small (<= ~500 chars)
    int N;
    int r = rnd.next(0, 99);
    if (r < 10) N = 1;
    else if (r < 20) N = 2;
    else N = rnd.next(3, 7); // 3..7

    // Choose a pattern for the cost matrix
    int pattern = rnd.next(0, 5);

    // Adjust pattern for very small N if needed
    if (N <= 2) {
        if (pattern == 2 || pattern == 3 || pattern == 5)
            pattern = rnd.next(0, 1); // use simpler patterns
    }
    if (N < 4 && pattern == 5)
        pattern = rnd.next(0, 4);
    if (N < 2 && pattern == 4)
        pattern = 0;

    vector<vector<long long>> c(N, vector<long long>(N, 0));

    switch (pattern) {
        case 0: {
            // Fully random moderate weights
            int hi = (N <= 4 ? 30 : 100);
            for (int i = 0; i < N; ++i) {
                c[i][i] = 0;
                for (int j = i + 1; j < N; ++j) {
                    long long val = rnd.next(1, hi);
                    c[i][j] = c[j][i] = val;
                }
            }
            break;
        }
        case 1: {
            // All off-diagonal weights equal
            long long base = rnd.next(1, 50);
            for (int i = 0; i < N; ++i) {
                c[i][i] = 0;
                for (int j = i + 1; j < N; ++j) {
                    c[i][j] = c[j][i] = base;
                }
            }
            break;
        }
        case 2: {
            // Star-like structure
            int center = rnd.next(0, N - 1);
            for (int i = 0; i < N; ++i) c[i][i] = 0;
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    long long val;
                    if (i == center || j == center) {
                        // Edges from/to center are relatively cheap
                        val = rnd.next(1, 20);
                    } else {
                        // Non-center edges mostly expensive, sometimes cheap
                        if (rnd.next(0, 3) == 0)
                            val = rnd.next(1, 30);
                        else
                            val = rnd.next(50, 100000000);
                    }
                    c[i][j] = c[j][i] = val;
                }
            }
            break;
        }
        case 3: {
            // Chain/line-like structure
            for (int i = 0; i < N; ++i) c[i][i] = 0;
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    long long val;
                    if (j == i + 1) {
                        // Neighbor edges small
                        val = rnd.next(1, 10);
                    } else {
                        // Non-neighbor edges: rarely small, usually huge
                        if (rnd.next(0, 4) == 0)
                            val = rnd.next(1, 50);
                        else
                            val = rnd.next(10000000, 100000000);
                    }
                    c[i][j] = c[j][i] = val;
                }
            }
            break;
        }
        case 4: {
            // Tree-dominant: build a random tree with small edges,
            // all other edges very large
            for (int i = 0; i < N; ++i) c[i][i] = 0;
            // Initialize all off-diagonal edges as huge
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    long long big = rnd.next(50000000, 100000000);
                    c[i][j] = c[j][i] = big;
                }
            }
            // Create a random tree on vertices 0..N-1
            for (int v = 1; v < N; ++v) {
                int p = rnd.next(0, v - 1);
                long long w = rnd.next(1, 50);
                c[v][p] = c[p][v] = w; // override with small weight
            }
            break;
        }
        case 5: {
            // Two-cluster structure
            for (int i = 0; i < N; ++i) c[i][i] = 0;
            vector<int> nodes(N);
            for (int i = 0; i < N; ++i) nodes[i] = i;
            shuffle(nodes.begin(), nodes.end());

            int sz1 = rnd.next(2, N - 2); // both clusters size >=2
            vector<int> isA(N, 0);
            for (int idx = 0; idx < sz1; ++idx) {
                isA[nodes[idx]] = 1;
            }

            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    long long val;
                    if (isA[i] == isA[j]) {
                        // Inside cluster: small/moderate weights
                        val = rnd.next(1, 30);
                    } else {
                        // Between clusters: usually large, sometimes small
                        if (rnd.next(0, 4) == 0)
                            val = rnd.next(1, 100);
                        else
                            val = rnd.next(50000000, 100000000);
                    }
                    c[i][j] = c[j][i] = val;
                }
            }
            break;
        }
        default:
            break;
    }

    // Output
    println(N);
    for (int i = 0; i < N; ++i) {
        println(c[i]);
    }

    return 0;
}
