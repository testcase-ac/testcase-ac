#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only says n is positive; use the local default cap for unspecified testcase counts.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readToken("[a-z]{1,20}", "name");
        inf.readEoln();
    }

    inf.readEof();
}
