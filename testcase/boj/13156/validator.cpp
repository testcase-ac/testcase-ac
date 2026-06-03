#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 100, "c");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    for (int merchant = 1; merchant <= m; ++merchant) {
        for (int cpus = 1; cpus <= c; ++cpus) {
            if (cpus > 1) {
                inf.readSpace();
            }
            inf.readInt(1, 100000, "p_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
