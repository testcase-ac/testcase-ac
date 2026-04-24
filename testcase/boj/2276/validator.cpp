#include "testlib.h"
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M (#columns) and N (#rows)
    int M = inf.readInt(1, 300, "M");
    inf.readSpace();
    int N = inf.readInt(1, 300, "N");
    inf.readEoln();

    // Read the height grid
    vector<vector<int>> h(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(M, 1, 1000000000, "h");
        for (int j = 0; j < M; j++) {
            h[i][j] = row[j];
        }
        inf.readEoln();
    }

    // Compute trapped water using the classic BFS with priority-queue (Dijkstra style)
    // to ensure the computed answer fits in a signed 32-bit int.
    const long long INT_MAX_LL = numeric_limits<int>::max();
    vector<vector<char>> vis(N, vector<char>(M, 0));
    // Min-heap of (height, x, y)
    priority_queue<
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<tuple<int,int,int>>
    > pq;

    // Push all boundary cells
    for (int i = 0; i < N; i++) {
        // left column
        vis[i][0] = 1;
        pq.emplace(h[i][0], i, 0);
        // right column
        if (M > 1) {
            vis[i][M-1] = 1;
            pq.emplace(h[i][M-1], i, M-1);
        }
    }
    for (int j = 0; j < M; j++) {
        // top row
        if (!vis[0][j]) {
            vis[0][j] = 1;
            pq.emplace(h[0][j], 0, j);
        }
        // bottom row
        if (N > 1 && !vis[N-1][j]) {
            vis[N-1][j] = 1;
            pq.emplace(h[N-1][j], N-1, j);
        }
    }

    static const int dx[4] = {1, -1, 0, 0};
    static const int dy[4] = {0, 0, 1, -1};

    long long total = 0;
    while (!pq.empty()) {
        auto [ch, x, y] = pq.top();
        pq.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            int nh = h[nx][ny];
            if (ch > nh) {
                total += (long long)(ch - nh);
            }
            int newH = max(nh, ch);
            pq.emplace(newH, nx, ny);
        }
    }

    // Check that the total trapped water fits in int
    ensuref(total <= INT_MAX_LL,
            "Total trapped water = %lld exceeds 32-bit signed int limit (%d)",
            total, (int)INT_MAX_LL);

    inf.readEof();
    return 0;
}
