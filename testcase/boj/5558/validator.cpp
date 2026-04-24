#include "testlib.h"
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H, W, N
    int H = inf.readInt(1, 1000, "H");
    inf.readSpace();
    int W = inf.readInt(1, 1000, "W");
    inf.readSpace();
    int N = inf.readInt(1, 9, "N");
    inf.readEoln();

    // Prepare to store the grid
    vector<string> grid(H);
    // Counters for 'S' and cheeses '1'..'N'
    int countS = 0;
    vector<int> countCheese(N+1, 0); // countCheese[k] for 'k'

    // Read each row
    for (int i = 0; i < H; i++) {
        // Regex: each line is exactly W characters in [S, '1'-'9', 'X', '.']
        string regex = "[S1-9X.]{" + to_string(W) + "," + to_string(W) + "}";
        grid[i] = inf.readLine(regex.c_str(), ("row_" + to_string(i+1)).c_str());
        // Count special cells
        for (int j = 0; j < W; j++) {
            char c = grid[i][j];
            if (c == 'S') {
                countS++;
            } else if ('1' <= c && c <= '9') {
                int k = c - '0';
                // If cheese label > N, it's invalid
                ensuref(k >= 1 && k <= N,
                        "Found cheese '%c' outside required range 1..%d at (%d,%d)",
                        c, N, i+1, j+1);
                countCheese[k]++;
            }
        }
    }

    // Validate exactly one 'S'
    ensuref(countS == 1, "There must be exactly one 'S', found %d", countS);
    // Validate exactly one cheese of each hardness 1..N
    for (int k = 1; k <= N; k++) {
        ensuref(countCheese[k] == 1,
                "There must be exactly one cheese '%d', found %d",
                k, countCheese[k]);
    }

    // Find positions of S and cheeses 1..N
    vector<pair<int,int>> pos(N+1, make_pair(-1,-1));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char c = grid[i][j];
            if (c == 'S') {
                pos[0] = make_pair(i, j);
            } else if ('1' <= c && c <= '9') {
                int k = c - '0';
                if (k >= 1 && k <= N) {
                    pos[k] = make_pair(i, j);
                }
            }
        }
    }
    // Sanity: all positions filled
    ensuref(pos[0].first != -1, "Position of 'S' not recorded");
    for (int k = 1; k <= N; k++) {
        ensuref(pos[k].first != -1, "Position of cheese '%d' not recorded", k);
    }

    // Prepare for BFS: directions
    const int DR[4] = { -1, 1, 0, 0 };
    const int DC[4] = { 0, 0, -1, 1 };

    // For each step: from pos[k-1] to pos[k], check reachable over non-'X' cells
    vector< vector<char> > seen(H, vector<char>(W, 0));
    queue<pair<int,int>> q;
    for (int k = 1; k <= N; k++) {
        // Reset seen and queue
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                seen[i][j] = 0;
        while (!q.empty()) q.pop();

        auto [sr, sc] = pos[k-1];
        auto [tr, tc] = pos[k];
        seen[sr][sc] = 1;
        q.emplace(sr, sc);
        bool reached = false;
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            if (r == tr && c == tc) {
                reached = true;
                break;
            }
            for (int d = 0; d < 4; d++) {
                int nr = r + DR[d], nc = c + DC[d];
                if (nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
                if (seen[nr][nc]) continue;
                if (grid[nr][nc] == 'X') continue;
                seen[nr][nc] = 1;
                q.emplace(nr, nc);
            }
        }
        ensuref(reached,
                "Cheese '%d' at (%d,%d) is unreachable from previous target at (%d,%d)",
                k, tr+1, tc+1, sr+1, sc+1);
    }

    inf.readEof();
    return 0;
}
