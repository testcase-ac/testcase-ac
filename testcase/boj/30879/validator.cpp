#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    bool hasQuery = false;
    for (int i = 1; i <= n; ++i) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            inf.readSpace();
            int a = inf.readInt(-100000, 100000, "a");
            inf.readSpace();
            int b = inf.readInt(-100000, 100000, "b");
            ensuref(a != 0, "a must be nonzero at action %d", i);
            ensuref(b != 0, "b must be nonzero at action %d", i);
        } else {
            hasQuery = true;
        }
        inf.readEoln();
    }

    ensuref(hasQuery, "at least one type 2 action is required");
    inf.readEof();
}
