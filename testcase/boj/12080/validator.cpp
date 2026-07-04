#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int s = inf.readInt(1, 100, "S");
        inf.readSpace();
        inf.readInt(1, 100, "R");
        inf.readSpace();
        inf.readInt(1, 100, "C");
        inf.readEoln();

        int previous_x = 0;
        for (int i = 1; i <= s; ++i) {
            int x = inf.readInt(1, 2000, "X_i");
            ensuref(previous_x < x,
                    "turn times must be strictly increasing: previous=%d, current=%d at action %d",
                    previous_x, x, i);
            previous_x = x;

            inf.readSpace();
            inf.readToken("L|R", "A_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
