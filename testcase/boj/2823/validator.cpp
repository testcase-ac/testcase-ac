#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R, C
    int R = inf.readInt(3, 10, "R");
    inf.readSpace();
    int C = inf.readInt(3, 10, "C");
    inf.readEoln();

    vector<string> grid(R);
    int totalRoads = 0;

    // Read the grid
    for (int i = 0; i < R; i++) {
        // readToken will read until whitespace; rows have no spaces
        string row = inf.readToken("[.X]+", "row");
        inf.readEoln();
        // check length
        ensuref((int)row.size() == C,
                "Row %d length must be %d, but got %d", i, C, (int)row.size());
        // check characters and count roads
        for (int j = 0; j < C; j++) {
            char ch = row[j];
            ensuref(ch == '.' || ch == 'X',
                    "Invalid character at row %d, col %d: expected '.' or 'X', got '%c'",
                    i, j, ch);
            if (ch == '.') totalRoads++;
        }
        grid[i] = row;
    }

    // At least two roads
    ensuref(totalRoads >= 2,
            "There must be at least two roads '.', but found %d", totalRoads);

    // Check connectivity of road cells via BFS
    vector<vector<bool>> vis(R, vector<bool>(C, false));
    int found_i = -1, found_j = -1;
    for (int i = 0; i < R && found_i == -1; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '.') {
                found_i = i;
                found_j = j;
                break;
            }
        }
    }
    // BFS
    queue<pair<int,int>> q;
    q.emplace(found_i, found_j);
    vis[found_i][found_j] = true;
    int reached = 0;
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        reached++;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < R && ny >= 0 && ny < C) {
                if (!vis[nx][ny] && grid[nx][ny] == '.') {
                    vis[nx][ny] = true;
                    q.emplace(nx, ny);
                }
            }
        }
    }
    ensuref(reached == totalRoads,
            "Road cells are not fully connected: reachable %d, total %d",
            reached, totalRoads);

    inf.readEof();
    return 0;
}
