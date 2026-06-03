#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readToken("[a-z]{1,100}", "word");
        inf.readEoln();
    }

    inf.readEof();
}
