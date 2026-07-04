#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int s = inf.readInt(1, 100000, "S");
        inf.readSpace();
        inf.readInt(1, 100000, "R");
        inf.readSpace();
        inf.readInt(1, 100000, "C");
        inf.readEoln();

        int previousTime = 0;
        for (int i = 1; i <= s; ++i) {
            int x = inf.readInt(1, 1000000, "X_i");
            inf.readSpace();
            string action = inf.readToken("L|R", "A_i");
            inf.readEoln();

            ensuref(previousTime < x,
                    "turn action times must be strictly increasing: previous=%d, current=%d at action %d",
                    previousTime, x, i);
            previousTime = x;
        }
    }

    inf.readEof();
}
