#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size
    int m = rnd.next(2, 8);
    int n = rnd.next(2, 8);
    // Initialize heights low
    vector<vector<int>> h(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            h[i][j] = rnd.next(1, 5);
    // Add some random peaks
    int peaks = rnd.next(0, 2);
    for (int t = 0; t < peaks; t++) {
        int x = rnd.next(0, m-1);
        int y = rnd.next(0, n-1);
        h[x][y] = rnd.next(8, 12);
    }
    // Decide barrier type: 0=none,1=horizontal,2=vertical
    vector<int> types = {0};
    if (m >= 3) types.push_back(1);
    if (n >= 3) types.push_back(2);
    int barrierType = rnd.any(types);
    int br = -1, bc = -1, gap = -1;
    if (barrierType == 1) {
        br = rnd.next(2, m-1);
        gap = rnd.next(1, n);
        int bh = rnd.next(10, 15);
        for (int j = 1; j <= n; j++) {
            if (j == gap) {
                h[br-1][j-1] = rnd.next(1, 5);
            } else {
                h[br-1][j-1] = bh;
            }
        }
    } else if (barrierType == 2) {
        bc = rnd.next(2, n-1);
        gap = rnd.next(1, m);
        int bh = rnd.next(10, 15);
        for (int i = 1; i <= m; i++) {
            if (i == gap) {
                h[i-1][bc-1] = rnd.next(1, 5);
            } else {
                h[i-1][bc-1] = bh;
            }
        }
    }
    // Number of queries
    int maxQ = min(15, m*n*2);
    int q;
    if (barrierType != 0) {
        q = rnd.next(2, maxQ);
    } else {
        q = rnd.next(1, maxQ);
    }
    // Generate queries
    vector<array<int,4>> qs;
    int cross = 0;
    if (barrierType != 0) {
        cross = rnd.next(1, q-1);
        // crossing queries
        for (int t = 0; t < cross; t++) {
            int x1, y1, x2, y2;
            if (barrierType == 1) {
                // horizontal barrier at br, start above, end below
                x1 = rnd.next(1, br-1);
                x2 = rnd.next(br+1, m);
                y1 = rnd.next(1, n);
                y2 = rnd.next(1, n);
            } else {
                // vertical barrier at bc, start left, end right
                y1 = rnd.next(1, bc-1);
                y2 = rnd.next(bc+1, n);
                x1 = rnd.next(1, m);
                x2 = rnd.next(1, m);
            }
            qs.push_back({x1, y1, x2, y2});
        }
    }
    // other random queries
    for (int t = cross; t < q; t++) {
        int x1 = rnd.next(1, m);
        int y1 = rnd.next(1, n);
        int x2 = rnd.next(1, m);
        int y2 = rnd.next(1, n);
        qs.push_back({x1, y1, x2, y2});
    }
    // Output
    println(m, n, q);
    for (int i = 0; i < m; i++) {
        println(h[i]);
    }
    for (auto &qq : qs) {
        println(qq[0], qq[1], qq[2], qq[3]);
    }
    return 0;
}
