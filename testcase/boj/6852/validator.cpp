#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 10000, "n");
        inf.readSpace();
        inf.readInt(1, 500, "k");
        inf.readSpace();
        inf.readInt(1, 100, "w");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readInt(-10000, 10000, "score");
            inf.readEoln();
        }
    }

    inf.readEof();
}
