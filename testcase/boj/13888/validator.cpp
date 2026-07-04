#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 16, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int G = inf.readInt(1, 50000, "G");
        inf.readSpace();
        inf.readInt(1, 50000, "W");
        inf.readEoln();

        inf.readInts(G, 1, 100000, "time");
        inf.readEoln();

        int Q = inf.readInt(1, 10000, "Q");
        inf.readEoln();

        for (int i = 1; i <= Q; ++i) {
            inf.readInt(1, G, "guest");
            inf.readSpace();
            inf.readInt(1, 100000, "updated_time");
            inf.readEoln();
        }
    }

    inf.readEof();
}
