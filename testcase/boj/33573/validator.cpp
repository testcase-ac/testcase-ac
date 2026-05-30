#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        inf.readLong(1LL, 1000000000000000000LL, "N");
        inf.readEoln();
    }

    inf.readEof();
}
