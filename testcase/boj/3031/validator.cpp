#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        bool known[5] = {false, false, false, false, false};
        int val[5] = {0, 0, 0, 0, 0};
        for (int j = 0; j < 5; j++) {
            if (j > 0) inf.readSpace();
            string name = "cell[" + to_string(i+1) + "][" + to_string(j+1) + "]";
            string tok = inf.readToken("0|[1-9][0-9]{0,2}|\\?", name.c_str());
            if (tok == "?") {
                known[j] = false;
            } else {
                known[j] = true;
                int x = stoi(tok);
                val[j] = x;
                if (j == 0) {
                    ensuref(0 <= x && x <= 100,
                            "Row %d: GP out of range (%d)", i+1, x);
                } else if (j == 1) {
                    ensuref(0 <= x && x <= 100,
                            "Row %d: W out of range (%d)", i+1, x);
                } else if (j == 2) {
                    ensuref(0 <= x && x <= 100,
                            "Row %d: D out of range (%d)", i+1, x);
                } else if (j == 3) {
                    ensuref(0 <= x && x <= 100,
                            "Row %d: L out of range (%d)", i+1, x);
                } else {
                    ensuref(0 <= x && x <= 300,
                            "Row %d: P out of range (%d)", i+1, x);
                }
            }
        }
        inf.readEoln();

        long long count = 0;
        for (int W = 0; W <= 100; W++) {
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
