#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the number of test cases; cap it at a
    // practical local limit while preserving the stated multi-case format.
    int c = inf.readInt(1, 100000, "c");
    inf.readEoln();

    for (int tc = 1; tc <= c; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 200000000, "n");
        inf.readSpace();
        int k1 = inf.readInt(0, n - 1, "k_1");
        inf.readSpace();
        int alpha = inf.readInt(1, min(100, n - 1), "alpha");
        inf.readEoln();

        (void)k1;
        (void)alpha;
    }

    inf.readEof();
}
