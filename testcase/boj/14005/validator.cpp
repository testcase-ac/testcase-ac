#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 3, "N");
    inf.readEoln();

    int playerCount = 1 << n;
    for (int i = 0; i < playerCount; ++i) {
        inf.readLong(0LL, 1000000000LL, "score");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
