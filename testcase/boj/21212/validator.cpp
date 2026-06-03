#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int required = inf.readInt(1, 10000, "required");
        inf.readSpace();
        int available = inf.readInt(1, 10000, "available");
        inf.readEoln();
    }

    inf.readEof();
}
