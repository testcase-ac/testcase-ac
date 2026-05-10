#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 100;
    const int M_MIN = 1;
    const int M_MAX = 1000000;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(M_MIN, M_MAX, "M");
    inf.readEoln();

    int start_r = -1, start_c = -1;
    bool hasStart = false;

    // Store map to allow later simulation if needed
    vector<vector<int>> grid(N, vector<int>(N));

    // Read map: each line has N integers separated by single spaces
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int cell = inf.readInt(0, 2, "cell");
            grid[i][j] = cell;

            if (cell == 2) {
                ensuref(!hasStart,
                        "Multiple starting positions found: previous at (%d,%d), another at (%d,%d)",
                        start_r, start_c, i + 1, j + 1);
                hasStart = true;
                start_r = i + 1;
                start_c = j + 1;
            }

            if (j + 1 < N)
                inf.readSpace();
        }
        inf.readEoln();
    }

    ensuref(hasStart, "No starting position (cell value 2) found in the map");

    // Read 4 event lines for W, A, S, D
    // Each line must be exactly one of "Down", "Stay", "Up"
    vector<string> keyNames = {"W", "A", "S", "D"};
    vector<string> events(4);
    for (int i = 0; i < 4; ++i) {
        string ev = inf.readToken("Down|Stay|Up", ("event_" + keyNames[i]).c_str());
        inf.readEoln();
        events[i] = ev;
    }

    // Read key presses string: exactly M characters, each in {W,A,S,D}
    // Whitespace-strict: whole line is that token, then EOLN.
    string presses = inf.readToken("[WASD]+", "presses");
    inf.readEoln();
    ensuref((int)presses.size() == M,
            "Length of presses string (%d) must equal M (%d)",
            (int)presses.size(), M);

    // No additional global guarantees in statement that require simulation,
    // so no need to simulate; map validity and input format are fully checked.

    inf.readEof();
}
