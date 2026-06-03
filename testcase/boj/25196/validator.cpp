#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 0; i < 3; ++i) {
        int v = inf.readInt(1, 2000, "v");
        inf.readSpace();
        int s = inf.readInt(0, 1999, "s");
        inf.readSpace();
        int e = inf.readInt(0, 1999, "e");
        inf.readEoln();

        ensuref(s <= e, "line %d has s > e: %d > %d", i + 1, s, e);
        ensuref(e < v, "line %d has e >= v: %d >= %d", i + 1, e, v);
    }

    inf.readEof();
}
