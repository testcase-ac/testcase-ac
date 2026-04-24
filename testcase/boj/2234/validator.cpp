#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions: N columns, M rows
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Read the castle map: M rows of N integers in [0,15]
    vector<vector<int>> a(M, vector<int>(N));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = inf.readInt(0, 15, "cell");
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    // Compute connected components (rooms) via BFS on no-wall adjacency
    vector<vector<int>> comp(M, vector<int>(N, 0));
    vector<int> compSize;  // 1-based indexing: comp IDs from 1...
    int compCnt = 0;
    const int dx[4] = {0, -1, 0, 1};   // west, north, east, south
    const int dy[4] = {-1, 0, 1, 0};
    const int wallBit[4] = {1, 2, 4, 8};
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (comp[i][j] == 0) {
                compCnt++;
                compSize.push_back(0);
                int cid = compCnt;
                queue<pair<int,int>> q;
                q.push({i, j});
                comp[i][j] = cid;
                while (!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    compSize[cid-1]++;
                    int mask = a[x][y];
                    // try all four directions where there is no wall
                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
                        // if there's a wall in direction d, we cannot go
                        if (mask & wallBit[d]) continue;
                        if (comp[nx][ny] == 0) {
                            comp[nx][ny] = cid;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }

    // Validate at least two rooms exist
    ensuref(compCnt >= 2,
            "Number of rooms must be at least 2, found %d", compCnt);

    // Validate that removing one wall can merge two distinct rooms
    bool canMerge = false;
    // check each cell's east and south walls to avoid double-check
    for (int i = 0; i < M && !canMerge; i++) {
        for (int j = 0; j < N && !canMerge; j++) {
            int mask = a[i][j];
            // east neighbor
            if (j+1 < N && (mask & 4)) {
                if (comp[i][j] != comp[i][j+1]) {
                    canMerge = true;
                    break;
                }
            }
            // south neighbor
            if (i+1 < M && (mask & 8)) {
                if (comp[i][j] != comp[i+1][j]) {
                    canMerge = true;
                    break;
                }
            }
        }
    }
    ensuref(canMerge,
            "No single wall removal can merge two distinct rooms");

    inf.readEof();
    return 0;
}
