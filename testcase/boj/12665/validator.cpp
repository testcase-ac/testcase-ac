#include "testlib.h"
#include <vector>
using namespace std;

bool hasSolution(int rows, int cols, const vector<vector<int>>& clues) {
    vector<int> masks;

    auto rowMatches = [&](int row) {
        for (int col = 0; col < cols; ++col) {
            int mines = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                int nr = row + dr;
                if (nr < 0 || nr >= rows) continue;
                for (int dc = -1; dc <= 1; ++dc) {
                    int nc = col + dc;
                    if (nc < 0 || nc >= cols) continue;
                    mines += (masks[nr] >> nc) & 1;
                }
            }
            if (mines != clues[row][col]) return false;
        }
        return true;
    };

    bool found = false;
    auto dfs = [&](auto&& self, int row) -> void {
        if (found) return;
        if (row == rows) {
            found = rowMatches(rows - 1);
            return;
        }

        for (int mask = 0; mask < (1 << cols); ++mask) {
            masks.push_back(mask);
            if (row == 0 || rowMatches(row - 1)) self(self, row + 1);
            masks.pop_back();
            if (found) return;
        }
    };

    dfs(dfs, 0);
    return found;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tests = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int test = 1; test <= tests; ++test) {
        setTestCase(test);

        int rows = inf.readInt(3, 5, "R");
        inf.readSpace();
        int cols = inf.readInt(3, 5, "C");
        inf.readEoln();

        ensuref(rows == 3 || rows == 5, "R must be 3 or 5, got %d", rows);
        ensuref(rows % 2 == 1, "R must be odd, got %d", rows);

        vector<vector<int>> clues(rows, vector<int>(cols));
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (col > 0) inf.readSpace();
                clues[row][col] = inf.readInt(0, 9, "clue");
            }
            inf.readEoln();
        }

        ensuref(hasSolution(rows, cols, clues), "case has no mine layout solution");
    }

    inf.readEof();
}
