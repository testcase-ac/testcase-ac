#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(3, 300, "N");
    inf.readSpace();
    int M = inf.readInt(3, 300, "M");
    inf.readEoln();

    // Read grid
    vector<vector<int>> a(N, vector<int>(M));
    int cntNonZero = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = inf.readInt(0, 10, "cell_value");
            if (j + 1 < M) inf.readSpace();
            if (a[i][j] > 0) cntNonZero++;
        }
        inf.readEoln();
    }

    // Boundary must be all zeros
    for (int j = 0; j < M; j++) {
        ensuref(a[0][j] == 0, "Boundary violation: a[0][%d] = %d (must be 0)", j, a[0][j]);
        ensuref(a[N-1][j] == 0, "Boundary violation: a[%d][%d] = %d (must be 0)", N-1, j, a[N-1][j]);
    }
    for (int i = 1; i < N-1; i++) {
        ensuref(a[i][0] == 0, "Boundary violation: a[%d][0] = %d (must be 0)", i, a[i][0]);
        ensuref(a[i][M-1] == 0, "Boundary violation: a[%d][%d] = %d (must be 0)", i, M-1, a[i][M-1]);
    }

    // Non-zero cells count limit
    ensuref(cntNonZero <= 10000,
            "Number of iceberg cells %d exceeds limit 10000", cntNonZero);

    // If there are any iceberg cells, they must form a single connected component
    if (cntNonZero > 0) {
        vector<vector<bool>> vis(N, vector<bool>(M, false));
        queue<pair<int,int>> q;
        // find start cell
        bool started = false;
        for (int i = 0; i < N && !started; i++) {
            for (int j = 0; j < M; j++) {
                if (a[i][j] > 0) {
                    q.emplace(i, j);
                    vis[i][j] = true;
                    started = true;
                    break;
                }
            }
        }
        int reached = 0;
        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            reached++;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                    if (!vis[nx][ny] && a[nx][ny] > 0) {
                        vis[nx][ny] = true;
                        q.emplace(nx, ny);
                    }
                }
            }
        }
        ensuref(reached == cntNonZero,
                "Iceberg not connected: reached %d of %d non-zero cells",
                reached, cntNonZero);
    }

    inf.readEof();
    return 0;
}
