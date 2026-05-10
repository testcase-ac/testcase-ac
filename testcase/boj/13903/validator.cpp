#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read R, C
    int R = inf.readInt(1, 1000, "R");
    inf.readSpace();
    int C = inf.readInt(1, 1000, "C");
    inf.readEoln();

    // 2. Read R lines of C integers: each is 0 or 1, separated by single spaces, no trailing/leading spaces
    vector<vector<int>> grid(R, vector<int>(C));
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            int val = inf.readInt(0, 1, format("block[%d][%d]", i+1, j+1).c_str());
            grid[i][j] = val;
            if (j + 1 < C) inf.readSpace();
        }
        inf.readEoln();
    }

    // 3. Read N (number of moves)
    int N = inf.readInt(0, 10, "N");
    inf.readEoln();

    // 4. Read N lines of r, c
    vector<pair<int,int>> moves;
    set<pair<int,int>> move_set;
    for (int i = 0; i < N; ++i) {
        int r = inf.readInt(-R, R, "r");
        inf.readSpace();
        int c = inf.readInt(-C, C, "c");
        inf.readEoln();
        ensuref(!(r == 0 && c == 0), "Move #%d is (0,0), which is not allowed", i+1);
        ensuref(move_set.count({r,c}) == 0, "Duplicate move (%d,%d) at line %d", r, c, i+1);
        move_set.insert({r,c});
        moves.push_back({r,c});
    }

    // 5. Formatting: ensure no extra lines
    inf.readEof();

    // 6. Global property: If the problem says "If 준규가 출근을 하는데 최소 몇 번의 걸음을 걸어야 하는지 출력한다. 만약 출근할 수 없다면 -1을 출력한다."
    // The problem does NOT guarantee that a path always exists, so we do NOT need to check for existence of a path.
    // However, we must check that at least one '1' exists in the first and last row, otherwise the answer is always -1.
    // But this is not a constraint, just a property of the input.

    // 7. Additional checks (implied by problem statement):
    // - Each line of the grid must have exactly C numbers, separated by single spaces, no leading/trailing spaces.
    // - Moves must not be (0,0).
    // - Moves must be unique.

    // 8. No further global properties to check, as the problem does not guarantee that a path always exists,
    // nor does it guarantee that the answer is at most X, etc.

    // All checks passed.
}
