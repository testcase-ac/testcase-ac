#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int v = inf.readInt(1, 25, "V");
    inf.readSpace();
    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    for (int i = 1; i <= v; ++i) {
        // CHECK: the statement says each coin value is an integer but gives no
        // separate bound; use the target-money bound as the practical cap.
        inf.readInt(1, 10000, "coin");
        inf.readEoln();
    }

    inf.readEof();
}
