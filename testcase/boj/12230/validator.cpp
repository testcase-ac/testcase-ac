#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 15, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readToken("E|L", "event");
            inf.readSpace();
            inf.readInt(0, 2000, "id");
            inf.readEoln();
        }
    }

    inf.readEof();
}
