#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    inf.readToken("[a-z]{3,25}", "name");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readToken("[a-z]{1,100}", "sign");
        inf.readEoln();
    }

    inf.readEof();
}
