#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readInt(2, 2147483647, "N");
        inf.readSpace();
        inf.readToken("Alice|Bob", "first_player");
        inf.readEoln();
    }

    inf.readEof();
}
