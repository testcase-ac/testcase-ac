#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of teams
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // For each team, read GP, W, D, L, P (note: sample implies D is third token, L fourth)
    for (int i = 0; i < N; i++) {
        bool known[5] = {false, false, false, false, false};
        int val[5] = {0, 0, 0, 0, 0};
        for (int j = 0; j < 5; j++) {
            if (j > 0) inf.readSpace();
            // cell name for error messages
            string name = "cell[" + to_string(i+1) + "][" + to_string(j+1) + "]";
            // token: either integer (1–3 digits) or '?'
            string tok = inf.readToken("[0-9]{1,3}|\\?", name.c_str());
            if (tok == "?") {
                known[j] = false;
            } else {
                known[j] = true;
                int x = stoi(tok);
                val[j] = x;
                // range checks per column
                if (j == 0) {
                    // GP: 0..100
                    ensuref(0 <= x && x <= 100,
                            "Row %d: GP out of range (%d)", i+1, x);
                } else if (j == 1) {
                    // W: 0..100
                    ensuref(0 <= x && x <= 100,
                            "Row %d: W out of range (%d)", i+1, x);
                } else if (j == 2) {
                    // D: 0..100
                    ensuref(0 <= x && x <= 100,
                            "Row %d: D out of range (%d)", i+1, x);
                } else if (j == 3) {
                    // L: 0..100
                    ensuref(0 <= x && x <= 100,
                            "Row %d: L out of range (%d)", i+1, x);
                } else {
                    // P: 0..300
                    ensuref(0 <= x && x <= 300,
                            "Row %d: P out of range (%d)", i+1, x);
                }
            }
        }
        inf.readEoln();

        // Count number of ways to fill missing fields such that
        //   GP = W + D + L
        //   P  = 3*W + D
        // and all values in [0..100] (GP<=100) and P<=300.
        long long count = 0;
        for (int W = 0; W <= 100; W++) {
            // prune by known W
            if (known[1] && val[1] != W) continue;
            for (int D = 0; D <= 100 - W; D++) {
                if (known[2] && val[2] != D) continue;
                for (int L = 0; L <= 100 - W - D; L++) {
                    if (known[3] && val[3] != L) continue;
                    int GP = W + D + L;
                    if (GP > 100) continue;
                    if (known[0] && val[0] != GP) continue;
                    int Pcalc = 3 * W + D;
                    if (Pcalc > 300) continue;
                    if (known[4] && val[4] != Pcalc) continue;
                    // found a valid fill
                    count++;
                    if (count > 1) break;
                }
                if (count > 1) break;
            }
            if (count > 1) break;
        }
        ensuref(count >= 1, "Row %d: no valid filling exists", i+1);
        ensuref(count == 1, "Row %d: filling is not unique (%lld ways)", i+1, count);
    }

    inf.readEof();
    return 0;
}
