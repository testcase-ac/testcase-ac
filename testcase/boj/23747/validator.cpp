#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid size
    int R = inf.readInt(1, 1000, "R");
    inf.readSpace();
    int C = inf.readInt(1, 1000, "C");
    inf.readEoln();

    // Read grid: R lines, each exactly C lowercase letters
    vector<string> grid(R);
    for (int i = 0; i < R; ++i) {
        grid[i] = inf.readLine("[a-z]{1,1000}", "grid_row");
        ensuref((int)grid[i].size() == C,
                "Row %d has length %d, expected %d", i + 1, (int)grid[i].size(), C);
    }

    // Read starting position
    int HR = inf.readInt(1, R, "H_R");
    inf.readSpace();
    int HC = inf.readInt(1, C, "H_C");
    inf.readEoln();

    // Read travel log: length <= 200000, chars in {U,D,L,R,W}
    string logStr = inf.readLine("[UDLRW]{0,200000}", "log");

    // Now validate global constraints implied by the problem
    // 1-based to 0-based
    int r = HR - 1;
    int c = HC - 1;

    // 1) At all times, Hanbyeol must stay inside the grid.
    // 2) We rely on grid indices being valid which is already ensured by movement check.
    for (int i = 0; i < (int)logStr.size(); ++i) {
        char ch = logStr[i];
        if (ch == 'U') {
            ensuref(r > 0, "Move U at step %d leaves grid (r=%d,c=%d)", i + 1, r + 1, c + 1);
            --r;
        } else if (ch == 'D') {
            ensuref(r + 1 < R, "Move D at step %d leaves grid (r=%d,c=%d)", i + 1, r + 1, c + 1);
            ++r;
        } else if (ch == 'L') {
            ensuref(c > 0, "Move L at step %d leaves grid (r=%d,c=%d)", i + 1, r + 1, c + 1);
            --c;
        } else if (ch == 'R') {
            ensuref(c + 1 < C, "Move R at step %d leaves grid (r=%d,c=%d)", i + 1, r + 1, c + 1);
            ++c;
        } else if (ch == 'W') {
            // W does not change position; nothing to validate here.
        } else {
            // This should be impossible due to regex, but keep safety.
            ensuref(false, "Invalid character '%c' in log at position %d", ch, i + 1);
        }
    }

    inf.readEof();
}
