#include "testlib.h"

static void readFlexibleArraySeparator() {
    int count = 0;
    while (true) {
        char c = inf.readChar();
        if (c == ' ' || c == '\n') {
            ++count;
            continue;
        }
        inf.unreadChar(c);
        break;
    }
    ensuref(count > 0, "expected whitespace between array values");
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // CHECK: the Korean text places all A[i] on the next line, but the
    // original English statement allows spaces and/or line breaks between them.
    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 1000000, "a_i");
        if (i < n) {
            readFlexibleArraySeparator();
        }
    }
    inf.readEoln();
    inf.readEof();
}
