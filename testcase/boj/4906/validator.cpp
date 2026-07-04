#include "testlib.h"

void readOneOrMoreSpaces() {
    inf.readSpace();
    while (true) {
        char c = inf.readChar();
        if (c != ' ') {
            inf.unreadChar(c);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        int n = inf.readInt(0, 999999, "n");
        readOneOrMoreSpaces();
        int d = inf.readInt(0, 999999, "d");
        inf.readEoln();

        if (n == 0 && d == 0) {
            ensuref(cases > 0, "input must contain at least one test case before the sentinel");
            break;
        }

        ++cases;
        ensuref(n >= 1, "n must be positive in test case %d, got %d", cases, n);
        ensuref(d >= 1, "d must be positive in test case %d, got %d", cases, d);
    }

    inf.readEof();
}
