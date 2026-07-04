#include "testlib.h"

#include <array>
#include <queue>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int kMinSize = 4;
constexpr int kMaxSize = 30;
constexpr int kDirections = 4;
const array<int, kDirections> dr{-1, 0, 1, 0};
const array<int, kDirections> dc{0, 1, 0, -1};

bool isStart(char ch) {
    return ch == 'N' || ch == 'E' || ch == 'S' || ch == 'W';
}

int startDirection(char ch) {
    if (ch == 'N') return 0;
    if (ch == 'E') return 1;
    if (ch == 'S') return 2;
    return 3;
}

bool isRoad(char ch) {
    return ch == '#' || ch == 'F' || isStart(ch);
}

bool hasValidRoute(const vector<string>& grid, int sr, int sc, int sd, int fr, int fc) {
    int h = static_cast<int>(grid.size());
    int w = static_cast<int>(grid[0].size());
    vector<vector<array<bool, kDirections>>> seen(
        h, vector<array<bool, kDirections>>(w, {false, false, false, false}));

    queue<array<int, 3>> q;
    seen[sr][sc][sd] = true;
    q.push({sr, sc, sd});

    while (!q.empty()) {
        auto [r, c, dir] = q.front();
        q.pop();

        if (r == fr && c == fc) {
            return true;
        }

        vector<int> nextDirs;
        for (int nd = 0; nd < kDirections; ++nd) {
            int nr = r + dr[nd];
            int nc = c + dc[nd];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                continue;
            }
            if (isRoad(grid[nr][nc])) {
                nextDirs.push_back(nd);
            }
        }

        for (int nd : nextDirs) {
            bool allowed = nd == dir || nd == (dir + 1) % kDirections ||
                           nd == (dir + 3) % kDirections ||
                           (nextDirs.size() == 1 && nd == (dir + 2) % kDirections);
            if (!allowed) {
                continue;
            }

            int nr = r + dr[nd];
            int nc = c + dc[nd];
            if (!seen[nr][nc][nd]) {
                seen[nr][nc][nd] = true;
                q.push({nr, nc, nd});
            }
        }
    }

    return false;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(kMinSize, kMaxSize, "h");
    inf.readSpace();
    int w = inf.readInt(kMinSize, kMaxSize, "w");
    inf.readEoln();

    vector<string> grid;
    int startCount = 0;
    int finishCount = 0;
    int sr = -1;
    int sc = -1;
    int sd = -1;
    int fr = -1;
    int fc = -1;

    for (int r = 0; r < h; ++r) {
        string row = inf.readToken("[.#EWNSF]{1,30}", "row");
        inf.readEoln();
        ensuref(static_cast<int>(row.size()) == w,
                "row %d has length %d, expected %d", r + 1,
                static_cast<int>(row.size()), w);

        for (int c = 0; c < w; ++c) {
            char ch = row[c];
            if (isStart(ch)) {
                ++startCount;
                sr = r;
                sc = c;
                sd = startDirection(ch);
            } else if (ch == 'F') {
                ++finishCount;
                fr = r;
                fc = c;
            }

            if (r == 0 || r == h - 1 || c == 0 || c == w - 1) {
                ensuref(ch == '.', "map frame cell (%d, %d) must be '.'", r + 1, c + 1);
            }
        }

        grid.push_back(row);
    }

    ensuref(startCount == 1, "expected exactly one start, found %d", startCount);
    ensuref(finishCount == 1, "expected exactly one finish, found %d", finishCount);
    ensuref(hasValidRoute(grid, sr, sc, sd, fr, fc),
            "finish is not reachable from the start under ERP movement rules");

    inf.readEof();
}
