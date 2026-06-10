#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 10000, "P");
    inf.readEoln();

    for (int i = 1; i <= p; ++i) {
        setTestCase(i);

        // CHECK: The statement names K as the data set number but gives no bound.
        int k = inf.readInt(1, 1000000000, "K");
        inf.readSpace();
        int n = inf.readInt(2, 10000, "N");
        inf.readEoln();

        (void)k;
        (void)n;
    }

    inf.readEof();
}
