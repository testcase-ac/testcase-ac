#include "testlib.h"

#include <algorithm>
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

bool canPlace(const vector<string>& board, const vector<string>& pattern, int top, int left) {
    int n = board.size();
    int side = pattern.size();
    const int dr[5] = {0, -1, 0, 1, 0};
    const int dc[5] = {0, 0, 1, 0, -1};

    for (int r = 0; r < side; ++r) {
        for (int c = 0; c < side; ++c) {
            if (pattern[r][c] != '#') continue;
            int br = top + r;
            int bc = left + c;
            for (int dir = 0; dir < 5; ++dir) {
                int nr = br + dr[dir];
                int nc = bc + dc[dir];
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                if (board[nr][nc] == '#') return false;
            }
        }
    }

    return true;
}

void place(vector<string>& board, const vector<string>& pattern, int top, int left) {
    int side = pattern.size();
    for (int r = 0; r < side; ++r) {
        for (int c = 0; c < side; ++c) {
            if (pattern[r][c] == '#') board[top + r][left + c] = '#';
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> possibleN = {5, 6, 7, 9, 11, 13, 17, 21, 25, 29};
    int n = rnd.any(possibleN);
    vector<string> board(n, string(n, '.'));

    int target = rnd.next(1, min(6, max(1, n / 4)));
    for (int placed = 0; placed < target; ++placed) {
        vector<int> sides;
        for (int side = 5; side <= min(n, 13); side += 4) sides.push_back(side);
        shuffle(sides.begin(), sides.end());

        bool done = false;
        for (int side : sides) {
            auto patterns = makePatterns(side);
            shuffle(patterns.begin(), patterns.end());

            vector<pair<int, int>> positions;
            for (int r = 0; r + side <= n; ++r) {
                for (int c = 0; c + side <= n; ++c) positions.push_back({r, c});
            }
            shuffle(positions.begin(), positions.end());

            for (const auto& pattern : patterns) {
                for (auto [top, left] : positions) {
                    if (!canPlace(board, pattern, top, left)) continue;
                    place(board, pattern, top, left);
                    done = true;
                    break;
                }
                if (done) break;
            }
            if (done) break;
        }
    }

    println(n);
    for (const string& row : board) println(row);

    return 0;
}
