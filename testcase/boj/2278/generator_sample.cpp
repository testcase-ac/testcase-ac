#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2;
    } else {
        n = rnd.next(3, 9);
    }

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, 0));

    if (mode == 0) {
        // Single vertex still has no distance rows; M remains constrained by input only.
    } else if (mode == 1) {
        dist[1][2] = dist[2][1] = rnd.next(1, 500);
    } else if (mode == 2) {
        int step = rnd.next(1, 30);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                dist[i][j] = dist[j][i] = (j - i) * step;
            }
        }
    } else if (mode == 3) {
        vector<int> pos(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            pos[i] = pos[i - 1] + rnd.next(1, 20);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                dist[i][j] = dist[j][i] = pos[j] - pos[i];
            }
        }
    } else if (mode == 4) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                dist[i][j] = dist[j][i] = rnd.next(1, 40);
            }
        }
    } else {
        int centerBias = rnd.next(1, 25);
        for (int i = 2; i <= n; ++i) {
            dist[1][i] = dist[i][1] = rnd.next(1, centerBias);
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int viaCenter = dist[1][i] + dist[1][j];
                dist[i][j] = dist[j][i] = rnd.next(1, min(500, viaCenter + rnd.next(0, 10)));
            }
        }
    }

    int maxEdges = n * (n - 1) / 2;
    int m;
    if (rnd.next(0, 4) == 0) {
        m = rnd.next(1, 1000);
    } else if (maxEdges == 0) {
        m = rnd.next(1, 3);
    } else {
        m = rnd.next(1, min(1000, maxEdges + rnd.next(0, 4)));
    }

    println(n, m);
    for (int i = 1; i <= n - 1; ++i) {
        vector<int> row;
        for (int j = i + 1; j <= n; ++j) {
            row.push_back(dist[i][j]);
        }
        println(row);
    }

    return 0;
}
