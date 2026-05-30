#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readToken("[A-Z]", "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
