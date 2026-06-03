#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int i = 1; i <= p; ++i) {
        // CHECK: The statement only says K is the data set number; keep it
        // positive and within int range without requiring ordering or uniqueness.
        int k = inf.readInt(1, 1000000000, "K");
        inf.readSpace();
        int n = inf.readInt(1, 2000, "N");
        inf.readEoln();
        setTestCase(i);
        (void)k;
        (void)n;
    }

    inf.readEof();
}
