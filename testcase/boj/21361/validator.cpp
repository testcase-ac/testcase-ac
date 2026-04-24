#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R, C, N
    int R = inf.readInt(3, 2000, "R");
    inf.readSpace();
    int C = inf.readInt(3, 2000, "C");
    inf.readSpace();
    int N = inf.readInt(1, 2000, "N");
    inf.readEoln();

    // Read command sequence
    string cmds = inf.readToken("[\\^><v]+", "commands");
    ensuref((int)cmds.size() == N,
            "Length of commands (%d) does not match N (%d)",
            (int)cmds.size(), N);
    inf.readEoln();

    // Read grid and validate
    int start_cnt = 0;
    for (int i = 0; i < R; i++) {
        // Each row must consist only of '.', '#', 'O'
        string row = inf.readLine("[\\.\\#O]+", "grid_row");
        ensuref((int)row.size() == C,
                "Row %d length is %d but expected %d",
                i+1, (int)row.size(), C);
        for (int j = 0; j < C; j++) {
            char ch = row[j];
            // Count start positions
            if (ch == 'O') {
                start_cnt++;
            }
            // Border cells must be '#'
            if (i == 0 || i == R-1 || j == 0 || j == C-1) {
                ensuref(ch == '#',
                        "Border cell at (%d,%d) is '%c' but must be '#'",
                        i+1, j+1, ch);
            }
            // Character must be one of the allowed
            ensuref(ch == '.' || ch == '#' || ch == 'O',
                    "Invalid character '%c' at grid cell (%d,%d)",
                    ch, i+1, j+1);
        }
    }
    ensuref(start_cnt == 1,
            "Number of start positions 'O' is %d but must be exactly 1",
            start_cnt);

    inf.readEof();
    return 0;
}
