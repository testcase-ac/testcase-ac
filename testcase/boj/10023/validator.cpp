#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int b = inf.readInt(1, 20, "B");
    inf.readEoln();

    for (int i = 0; i < b; ++i) {
        inf.readInt(1, 100, "V_i");
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 100000, "field_volume_i");
        inf.readEoln();
    }

    inf.readEof();
}
