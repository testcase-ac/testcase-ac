#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        for (int row = 0; row < 3; ++row) {
            inf.readToken("H|T", "coin");
            inf.readSpace();
            inf.readToken("H|T", "coin");
            inf.readSpace();
            inf.readToken("H|T", "coin");
            inf.readEoln();
        }
    }

    inf.readEof();
}
