#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXC = 200000;

    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // Read boxes
    // Positions must be unique
    set<pair<int,int>> pos;
    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(1, MAXC, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, MAXC, "y_i");
        inf.readSpace();
        int w = inf.readInt(1, 200000, "w_i");
        inf.readEoln();

        pair<int,int> p = {x, y};
        ensuref(!pos.count(p),
                "Box positions must be unique, but (%d, %d) appears multiple times (at least at index %d).",
                x, y, i);
        pos.insert(p);
    }

    long long x = 1, y = 1;
    // Simulate moves to ensure car always stays in bounds
    for (int j = 0; j < Q; ++j) {
        int d = inf.readInt(0, 3, "d_j");
        inf.readSpace();
        int v = inf.readInt(1, MAXC, "v_j");
        inf.readEoln();

        if (d == 0) {
            // x increases
            long long nx = x + v;
            ensuref(1LL <= nx && nx <= MAXC,
                    "After move %d, x-coordinate %lld is out of bounds [1, %d].",
                    j, nx, MAXC);
            x = nx;
        } else if (d == 1) {
            // y increases
            long long ny = y + v;
            ensuref(1LL <= ny && ny <= MAXC,
                    "After move %d, y-coordinate %lld is out of bounds [1, %d].",
                    j, ny, MAXC);
            y = ny;
        } else if (d == 2) {
            // x decreases
            long long nx = x - v;
            ensuref(1LL <= nx && nx <= MAXC,
                    "After move %d, x-coordinate %lld is out of bounds [1, %d].",
                    j, nx, MAXC);
            x = nx;
        } else { // d == 3
            // y decreases
            long long ny = y - v;
            ensuref(1LL <= ny && ny <= MAXC,
                    "After move %d, y-coordinate %lld is out of bounds [1, %d].",
                    j, ny, MAXC);
            y = ny;
        }
    }

    inf.readEof();
}
