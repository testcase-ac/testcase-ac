#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 50, "N");
        inf.readSpace();
        inf.readInt(0, 1000000000, "K");
        inf.readEoln();

        for (int row = 1; row <= 4; ++row) {
            inf.readInts(N, 0, 1000000000, "robot_number");
            inf.readEoln();
        }
    }

    inf.readEof();
}
