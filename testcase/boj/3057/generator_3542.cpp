#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

bool findKiller(const vector<string>& g, int R, int C, int& out_k, int& out_i, int& out_j) {
    int maxK = min(R, C);
    // search for any killer square, prefer larger sizes first
    for (int k = maxK; k >= 2; --k) {
        for (int i = 0; i + k <= R; ++i) {
            for (int j = 0; j + k <= C; ++j) {
                bool ok = true;
                for (int u = 0; u < k && ok; ++u) {
                    for (int v = 0; v < k; ++v) {
                        if (g[i+u][j+v] != g[i+k-1-u][j+k-1-v]) {
                            ok = false;
                            break;
                        }
                    }
                }
                if (ok) {
                    out_k = k;
                    out_i = i;
                    out_j = j;
                    return true;
                }
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose dimensions
    int R = rnd.next(1, 10);
    int C = rnd.next(1, 10);

    // Decide if we want at least one killer
    bool wantKiller = rnd.next(0, 1) == 1;

    vector<string> grid;
    if (wantKiller) {
        // ensure room for a killer
        R = rnd.next(2, 10);
        C = rnd.next(2, 10);
        grid.assign(R, string(C, '0'));
        // fill randomly
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                grid[i][j] = char('0' + rnd.next(0, 1));
        // pick a killer size, bias randomly
        int maxK = min(R, C);
        int t = rnd.next(-1, 1);
        int K = rnd.wnext(maxK - 1, t) + 2; // in [2..maxK]
        int si = rnd.next(0, R - K);
        int sj = rnd.next(0, C - K);
        // embed a symmetric square of size K
        for (int u = 0; u < K; ++u) {
            for (int v = 0; v < K; ++v) {
                int x1 = si + u, y1 = sj + v;
                int x2 = si + (K - 1 - u), y2 = sj + (K - 1 - v);
                if (x1 < x2 || (x1 == x2 && y1 <= y2)) {
                    char b = char('0' + rnd.next(0, 1));
                    grid[x1][y1] = b;
                    grid[x2][y2] = b;
                }
            }
        }
    } else {
        // negative case: generate and break all killers
        R = rnd.next(1, 10);
        C = rnd.next(1, 10);
        grid.assign(R, string(C, '0'));
        // initial random fill
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                grid[i][j] = char('0' + rnd.next(0, 1));
        // iteratively remove any found killer by flipping a random bit in it
        int k0, i0, j0;
        while (findKiller(grid, R, C, k0, i0, j0)) {
            int u = rnd.next(0, k0 - 1);
            int v = rnd.next(0, k0 - 1);
            int x = i0 + u, y = j0 + v;
            grid[x][y] = (grid[x][y] == '0' ? '1' : '0');
        }
    }

    // output
    println(R, C);
    for (int i = 0; i < R; ++i)
        printf("%s\n", grid[i].c_str());

    return 0;
}
