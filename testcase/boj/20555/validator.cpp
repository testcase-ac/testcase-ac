#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 6, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readToken("[A-D]{1,9}", "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
