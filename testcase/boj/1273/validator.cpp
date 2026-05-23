#include "testlib.h"
#include <climits>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "black");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "gray");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "white");
    inf.readEoln();

    int m = inf.readInt(1, 300000, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(1, LLONG_MAX, "shot_height");
    }
    inf.readEoln();

    inf.readEof();
}
