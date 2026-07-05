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
    vector<string> grid;
};

vector<TestCase> cases;

pair<int, int> transformCell(pair<int, int> cell, int transform) {
    int r = cell.first;
    int c = cell.second;
    switch (transform) {
        case 0: return {r, c};
        case 1: return {r, -c};
        case 2: return {-r, c};
        case 3: return {-r, -c};
        case 4: return {c, r};
        case 5: return {c, -r};
        case 6: return {-c, r};
        case 7: return {-c, -r};
    }
    quitf(_fail, "internal error: unknown transform %d", transform);
}

vector<pair<int, int>> normalize(vector<pair<int, int>> cells) {
    int minRow = cells[0].first;
    int minCol = cells[0].second;
    for (auto [r, c] : cells) {
        minRow = min(minRow, r);
        minCol = min(minCol, c);
    }
    for (auto& [r, c] : cells) {
        r -= minRow;
        c -= minCol;
    }
    sort(cells.begin(), cells.end());
    return cells;
}

bool sameShape(const vector<pair<int, int>>& red, const vector<pair<int, int>>& blue) {
    if (red.size() != blue.size()) {
        return false;
    }

    vector<pair<int, int>> target = normalize(blue);
    for (int transform = 0; transform < 8; ++transform) {
        vector<pair<int, int>> changed;
        changed.reserve(red.size());
        for (auto cell : red) {
            changed.push_back(transformCell(cell, transform));
        }
        if (normalize(changed) == target) {
            return true;
        }
    }
    return false;
}

Claim readClaim(InStream& stream, const TestCase& tc, int index) {
    string first = stream.readToken("IMPOSSIBLE|[RB]+",
                                    format("case %d first output token", index).c_str());
    if (first == "IMPOSSIBLE") {
        return {true, {}};
    }

    vector<string> grid(tc.rows);
    grid[0] = first;
    for (int r = 1; r < tc.rows; ++r) {
        grid[r] = stream.readToken("[RB]+", format("case %d row %d", index, r + 1).c_str());
    }

    vector<pair<int, int>> red;
    vector<pair<int, int>> blue;
    for (int r = 0; r < tc.rows; ++r) {
        if ((int)grid[r].size() != tc.cols) {
            stream.quitf(_wa,
                         "case %d row %d has length %d instead of %d",
                         index,
                         r + 1,
                         (int)grid[r].size(),
                         tc.cols);
        }
        for (int c = 0; c < tc.cols; ++c) {
            if (grid[r][c] == 'R') {
                red.push_back({r, c});
            } else {
                blue.push_back({r, c});
            }
        }
    }

    if (grid[tc.redRow][tc.redCol] != 'R') {
        stream.quitf(_wa, "case %d fixed red cell is not red", index);
    }
    if (grid[tc.blueRow][tc.blueCol] != 'B') {
        stream.quitf(_wa, "case %d fixed blue cell is not blue", index);
    }
    if (red.size() != blue.size()) {
        stream.quitf(_wa,
                     "case %d has %d red cells and %d blue cells",
                     index,
                     (int)red.size(),
                     (int)blue.size());
    }
    if (!sameShape(red, blue)) {
        stream.quitf(_wa, "case %d red and blue parts do not have the same shape", index);
    }

    return {false, grid};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt(1, 100000, "t");
    cases.resize(testCount);
    for (int i = 0; i < testCount; ++i) {
        int rows = inf.readInt(1, 100, "r");
        int cols = inf.readInt(1, 100, "c");
        int redRow = inf.readInt(1, rows, "r_r") - 1;
        int redCol = inf.readInt(1, cols, "c_r") - 1;
        int blueRow = inf.readInt(1, rows, "r_b") - 1;
        int blueCol = inf.readInt(1, cols, "c_b") - 1;
        cases[i] = {rows, cols, redRow, redCol, blueRow, blueCol};
    }

    for (int i = 0; i < testCount; ++i) {
        Claim jury = readClaim(ans, cases[i], i + 1);
        Claim participant = readClaim(ouf, cases[i], i + 1);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "case %d: participant found a valid coloring but jury says IMPOSSIBLE", i + 1);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "case %d: jury has a valid coloring but participant says IMPOSSIBLE", i + 1);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }
    quitf(_ok, "%d case(s) checked", testCount);
}
