#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size: small for hand-checkable
    int N = rnd.next(1, 10);
    // Excavator type
    char type = rnd.any(string("RQBNK"));
    // Number of stones M, biased towards smaller counts but at least 1
    int maxM = min(N * N, 2 * N);
    int M;
    if (rnd.next(0, 3) == 0) {
        // occasionally pick any size up to maxM
        M = rnd.next(1, maxM);
    } else {
        // bias to smaller: square root bias
        int x = rnd.next(1, maxM);
        M = max(1, int(sqrt(x)));
        if (M > maxM) M = maxM;
    }
    // Choose a placement pattern: avoid line pattern if M > N
    int clusterType;
    if (M > N) {
        clusterType = rnd.next(0, 1); // only random or clustered
    } else {
        clusterType = rnd.next(0, 2);
    }
    vector<pair<int,int>> pos;
    if (clusterType == 0) {
        // fully random distinct positions
        vector<pair<int,int>> all;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        pos.assign(all.begin(), all.begin() + M);
    } else if (clusterType == 1) {
        // clustered around an anchor
        int ax = rnd.next(1, N), ay = rnd.next(1, N);
        int R = rnd.next(1, max(1, N/2));
        vector<pair<int,int>> cluster;
        for (int dx = -R; dx <= R; dx++) {
            for (int dy = -R; dy <= R; dy++) {
                int x = ax + dx, y = ay + dy;
                if (1 <= x && x <= N && 1 <= y && y <= N)
                    cluster.emplace_back(x, y);
            }
        }
        shuffle(cluster.begin(), cluster.end());
        if ((int)cluster.size() >= M) {
            pos.assign(cluster.begin(), cluster.begin() + M);
        } else {
            // take all cluster, then fill from rest
            pos = cluster;
            vector<pair<int,int>> rest;
            vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
            for (auto &p : pos) used[p.first][p.second] = true;
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    if (!used[i][j])
                        rest.emplace_back(i, j);
            shuffle(rest.begin(), rest.end());
            int need = M - (int)pos.size();
            for (int i = 0; i < need && i < (int)rest.size(); i++)
                pos.push_back(rest[i]);
        }
    } else {
        // all on one row or one column, only valid if M <= N
        bool isRow = rnd.next(0,1) == 1;
        if (isRow) {
            int row = rnd.next(1, N);
            vector<int> cols(N);
            for (int i = 0; i < N; i++) cols[i] = i+1;
            shuffle(cols.begin(), cols.end());
            for (int i = 0; i < M; i++)
                pos.emplace_back(row, cols[i]);
        } else {
            int col = rnd.next(1, N);
            vector<int> rows(N);
            for (int i = 0; i < N; i++) rows[i] = i+1;
            shuffle(rows.begin(), rows.end());
            for (int i = 0; i < M; i++)
                pos.emplace_back(rows[i], col);
        }
    }
    // Build grid
    vector<string> grid(N, string(N, '.'));
    for (auto &p : pos)
        grid[p.first - 1][p.second - 1] = type;
    // Output
    printf("%d %c\n", N, type);
    for (int i = 0; i < N; i++)
        printf("%s\n", grid[i].c_str());
    return 0;
}
