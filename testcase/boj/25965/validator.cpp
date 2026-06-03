#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int game = 1; game <= n; ++game) {
        setTestCase(game);

        int m = inf.readInt(1, 100, "M");
        inf.readEoln();

        for (int mission = 1; mission <= m; ++mission) {
            inf.readInt(1000, 50000000, "K");
            inf.readSpace();
            inf.readInt(1000, 50000000, "D");
            inf.readSpace();
            inf.readInt(1000, 50000000, "A");
            inf.readEoln();
        }

        inf.readInt(0, 50, "k");
        inf.readSpace();
        inf.readInt(0, 50, "d");
        inf.readSpace();
        inf.readInt(0, 50, "a");
        inf.readEoln();
    }

    inf.readEof();
}
