#include "testlib.h"
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, L, R
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int L = inf.readInt(1, 100, "L");
    inf.readSpace();
    int R = inf.readInt(L, 100, "R");
    inf.readEoln();

    // Read the population grid A
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = inf.readInt(0, 100, (string("A[") + to_string(i) + "][" + to_string(j) + "]").c_str());
            if (j + 1 < N) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // Simulate the population movement to ensure the number of days <= 2000
    int days = 0;
    const int DX[4] = {-1, 1, 0, 0};
    const int DY[4] = {0, 0, -1, 1};
    vector<vector<bool>> vis(N, vector<bool>(N));

    while (true) {
        // Reset visited and prepare new grid
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                vis[i][j] = false;
        vector<vector<int>> newA = A;

        bool moved = false;
        // Find all unions via BFS
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (vis[i][j]) continue;
                queue<pair<int,int>> q;
                vector<pair<int,int>> cells;
                q.push({i,j});
                vis[i][j] = true;
                cells.push_back({i,j});
                int sumPop = A[i][j];

                while (!q.empty()) {
                    auto [x,y] = q.front(); q.pop();
                    for (int d = 0; d < 4; d++) {
                        int nx = x + DX[d], ny = y + DY[d];
                        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                        if (vis[nx][ny]) continue;
                        int diff = abs(A[x][y] - A[nx][ny]);
                        if (diff < L || diff > R) continue;
                        // open border
                        vis[nx][ny] = true;
                        q.push({nx,ny});
                        cells.push_back({nx,ny});
                        sumPop += A[nx][ny];
                    }
                }

                if ((int)cells.size() > 1) {
                    moved = true;
                    int avg = sumPop / (int)cells.size();
                    for (auto &p : cells) {
                        newA[p.first][p.second] = avg;
                    }
                }
            }
        }

        if (!moved) break;
        days++;
        ensuref(days <= 2000, "Number of days %d exceeds limit of 2000", days);
        A.swap(newA);
    }

    inf.readEof();
    return 0;
}
