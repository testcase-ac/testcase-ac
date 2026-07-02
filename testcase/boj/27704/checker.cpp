#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct TestCase {
    int rows;
    int cols;
    int redRow;
    int redCol;
    int blueRow;
    int blueCol;
};

struct Claim {
    bool impossible;
};

vector<pair<int, int>> normalize(vector<pair<int, int>> cells) {
    int minRow = cells[0].first;
    int minCol = cells[0].second;
    for (const auto& cell : cells) {
        minRow = min(minRow, cell.first);
        minCol = min(minCol, cell.second);
    }
    for (auto& cell : cells) {
        cell.first -= minRow;
        cell.second -= minCol;
    }
    sort(cells.begin(), cells.end());
    return cells;
}

vector<pair<int, int>> transformCells(const vector<pair<int, int>>& cells, int transform) {
    vector<pair<int, int>> result;
    result.reserve(cells.size());
    for (const auto& [r, c] : cells) {
        int nr = 0;
        int nc = 0;
        if (transform == 0) {
            nr = r;
            nc = c;
        } else if (transform == 1) {
            nr = r;
            nc = -c;
        } else if (transform == 2) {
            nr = -r;
            nc = c;
        } else if (transform == 3) {
            nr = -r;
            nc = -c;
        } else if (transform == 4) {
            nr = c;
            nc = r;
        } else if (transform == 5) {
            nr = c;
            nc = -r;
        } else if (transform == 6) {
            nr = -c;
            nc = r;
        } else {
            nr = -c;
            nc = -r;
        }
        result.push_back({nr, nc});
    }
    return normalize(result);
}

bool sameShape(const vector<pair<int, int>>& red, const vector<pair<int, int>>& blue) {
    if (red.size() != blue.size()) {
        return false;
    }
    vector<pair<int, int>> normalizedBlue = normalize(blue);
    for (int transform = 0; transform < 8; ++transform) {
        if (transformCells(red, transform) == normalizedBlue) {
            return true;
        }
    }
    return false;
}

bool connected(const vector<string>& board, char color) {
    int rows = int(board.size());
    int cols = int(board[0].size());
    vector<pair<int, int>> cells;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (board[r][c] == color) {
                cells.push_back({r, c});
            }
        }
    }
    if (cells.empty()) {
        return false;
    }

    vector<vector<int>> seen(rows, vector<int>(cols, 0));
    vector<pair<int, int>> stack = {cells[0]};
    seen[cells[0].first][cells[0].second] = 1;
    int visited = 0;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    while (!stack.empty()) {
        auto [r, c] = stack.back();
        stack.pop_back();
        ++visited;
        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                continue;
            }
            if (seen[nr][nc] || board[nr][nc] != color) {
                continue;
            }
            seen[nr][nc] = 1;
            stack.push_back({nr, nc});
        }
    }
    return visited == int(cells.size());
}

Claim readClaim(InStream& stream, const TestCase& tc, int caseIndex) {
    string first = stream.readToken();
    if (first == "IMPOSSIBLE") {
        return {true};
    }

    vector<string> board(tc.rows);
    board[0] = first;
    for (int r = 1; r < tc.rows; ++r) {
        board[r] = stream.readToken();
    }

    vector<pair<int, int>> red;
    vector<pair<int, int>> blue;
    for (int r = 0; r < tc.rows; ++r) {
        if (int(board[r].size()) != tc.cols) {
            stream.quitf(_wa, "case %d row %d has length %d instead of %d",
                         caseIndex, r + 1, int(board[r].size()), tc.cols);
        }
        for (int c = 0; c < tc.cols; ++c) {
            if (board[r][c] == 'R') {
                red.push_back({r, c});
            } else if (board[r][c] == 'B') {
                blue.push_back({r, c});
            } else {
                stream.quitf(_wa, "case %d row %d column %d has invalid character '%c'",
                             caseIndex, r + 1, c + 1, board[r][c]);
            }
        }
    }

    if (board[tc.redRow - 1][tc.redCol - 1] != 'R') {
        stream.quitf(_wa, "case %d red fixed square is not R", caseIndex);
    }
    if (board[tc.blueRow - 1][tc.blueCol - 1] != 'B') {
        stream.quitf(_wa, "case %d blue fixed square is not B", caseIndex);
    }
    if (red.size() != blue.size()) {
        stream.quitf(_wa, "case %d has %d red cells and %d blue cells",
                     caseIndex, int(red.size()), int(blue.size()));
    }
    if (!connected(board, 'R')) {
        stream.quitf(_wa, "case %d red part is not connected", caseIndex);
    }
    if (!connected(board, 'B')) {
        stream.quitf(_wa, "case %d blue part is not connected", caseIndex);
    }
    if (!sameShape(red, blue)) {
        stream.quitf(_wa, "case %d red and blue parts do not have the same shape", caseIndex);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    vector<TestCase> cases(testCount);
    for (int i = 0; i < testCount; ++i) {
        cases[i].rows = inf.readInt();
        cases[i].cols = inf.readInt();
        cases[i].redRow = inf.readInt();
        cases[i].redCol = inf.readInt();
        cases[i].blueRow = inf.readInt();
        cases[i].blueCol = inf.readInt();
    }

    for (int i = 0; i < testCount; ++i) {
        Claim jury = readClaim(ans, cases[i], i + 1);
        Claim participant = readClaim(ouf, cases[i], i + 1);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "case %d participant found a valid coloring while jury says IMPOSSIBLE", i + 1);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "case %d jury has a valid coloring but participant says IMPOSSIBLE", i + 1);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }
    quitf(_ok, "all %d case(s) are valid", testCount);
}
