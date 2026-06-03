#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only says n is positive; use the local default cap.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        setTestCase(i + 1);
        inf.readToken("[a-z]{1,100}", "s");
        inf.readEoln();
    }

    inf.readEof();
}
