#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 1000000, "cow_id");
        inf.readEoln();
    }

    inf.readEof();
}
