#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 15, "N");
    for (int i = 0; i < n; ++i) {
        inf.readSpace();
        inf.readInt(1, 5000, "time");
    }
    inf.readEoln();
    inf.readEof();
}
