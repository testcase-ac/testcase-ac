#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int R = inf.readInt(3, 250, "R");
    inf.readSpace();
    int C = inf.readInt(3, 250, "C");
    inf.readEoln();

    // Read grid
    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
        // Read an arbitrary line, then validate length and characters
        string s = inf.readLine("[^]*", "row");
        ensuref((int)s.size() == C,
                "Row %d has incorrect length: expected %d, found %d",
                i+1, C, (int)s.size());
        for (int j = 0; j < C; j++) {
            char ch = s[j];
            ensuref(ch == '.' || ch == '#' || ch == 'v' || ch == 'k',
                    "Invalid character '%c' at row %d, column %d", ch, i+1, j+1);
        }
        grid[i] = s;
    }

    // Ensure that no sheep ('k') or wolves ('v') are in the outside (non-fenced) area.
    // We perform a BFS from all boundary cells that are not '#', and check we never see 'k' or 'v'.
    vector<vector<bool>> vis(R, vector<bool>(C, false));
    queue<pair<int,int>> q;
    auto try_push = [&](int x, int y) {
        if (x < 0 || x >= R || y < 0 || y >= C) return;
        if (vis[x][y]) return;
        if (grid[x][y] == '#') return;
        vis[x][y] = true;
        q.emplace(x, y);
    };

    // Initialize BFS from boundary non-fence cells
    for (int i = 0; i < R; i++) {
        try_push(i, 0);
        try_push(i, C-1);
    }
    for (int j = 0; j < C; j++) {
        try_push(0, j);
        try_push(R-1, j);
    }

    // Directions for 4-neighbors
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    // BFS and check
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        char ch = grid[x][y];
        ensuref(ch == '.',
                "Animal '%c' found in non-fenced area at (%d, %d)",
                ch, x+1, y+1);
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            try_push(nx, ny);
        }
    }

    // End of input
    inf.readEof();
    return 0;
}
