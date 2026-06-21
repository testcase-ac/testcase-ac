#include "testlib.h"

#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

vector<string> makePattern(int side, int startR, int startC, const string& dirs) {
    vector<string> pattern(side, string(side, '.'));
    int r = startR;
    int c = startC;
    pattern[r][c] = '#';

    int len = side - 1;
    int dirIndex = 0;
    bool firstLayer = true;
    while (len > 0) {
        int turns = firstLayer ? 3 : 2;
        firstLayer = false;

        for (int turn = 0; turn < turns; ++turn) {
            char dir = dirs[dirIndex % 4];
            ++dirIndex;
            for (int step = 0; step < len; ++step) {
                if (dir == 'U') --r;
                if (dir == 'D') ++r;
                if (dir == 'L') --c;
                if (dir == 'R') ++c;
                pattern[r][c] = '#';
            }
        }
        len -= 2;
    }

    return pattern;
}

vector<vector<string>> makePatterns(int side) {
    return {
        makePattern(side, 0, 0, "DRUL"),
        makePattern(side, 0, side - 1, "DLUR"),
        makePattern(side, side - 1, 0, "URDL"),
        makePattern(side, side - 1, side - 1, "ULDR"),
        makePattern(side, 0, 0, "RDLU"),
        makePattern(side, 0, side - 1, "LDRU"),
        makePattern(side, side - 1, 0, "RULD"),
        makePattern(side, side - 1, side - 1, "LURD"),
    };
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 1250, "N");
    inf.readEoln();

    vector<string> board(n);
    for (int i = 0; i < n; ++i) {
        board[i] = inf.readToken("[.#]{" + to_string(n) + "}", "row");
        inf.readEoln();
    }
    inf.readEof();

    vector<vector<int>> seen(n, vector<int>(n, 0));
    int fossilCount = 0;
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    for (int sr = 0; sr < n; ++sr) {
        for (int sc = 0; sc < n; ++sc) {
            if (board[sr][sc] != '#' || seen[sr][sc]) continue;

            ++fossilCount;
            vector<pair<int, int>> cells;
            queue<pair<int, int>> q;
            q.push({sr, sc});
            seen[sr][sc] = 1;
            int minR = sr, maxR = sr, minC = sc, maxC = sc;

            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                cells.push_back({r, c});
                minR = min(minR, r);
                maxR = max(maxR, r);
                minC = min(minC, c);
                maxC = max(maxC, c);

                for (int dir = 0; dir < 4; ++dir) {
                    int nr = r + dr[dir];
                    int nc = c + dc[dir];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                    if (board[nr][nc] != '#' || seen[nr][nc]) continue;
                    seen[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }

            int height = maxR - minR + 1;
            int width = maxC - minC + 1;
            ensuref(height == width,
                    "component at (%d, %d) has non-square bounding box %dx%d",
                    sr + 1, sc + 1, height, width);
            ensuref(height >= 5 && height % 4 == 1,
                    "component at (%d, %d) has invalid side length %d",
                    sr + 1, sc + 1, height);

            vector<string> actual(height, string(width, '.'));
            for (auto [r, c] : cells) {
                actual[r - minR][c - minC] = '#';
            }

            bool matches = false;
            for (const auto& pattern : makePatterns(height)) {
                if (actual == pattern) {
                    matches = true;
                    break;
                }
            }
            ensuref(matches, "component at (%d, %d) is not a valid fossil spiral",
                    sr + 1, sc + 1);
        }
    }

    ensuref(fossilCount >= 1, "at least one fossil is required");
}
