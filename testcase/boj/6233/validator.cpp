#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readToken("F|B", "direction");
        inf.readEoln();
    }

    inf.readEof();
}
