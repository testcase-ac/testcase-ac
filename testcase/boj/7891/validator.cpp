#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int i = 0; i < t; ++i) {
        setTestCase(i + 1);

        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y");
        inf.readEoln();

        // No extra global properties to check; problem doesn't guarantee anything
        // about the sum (it may overflow 32-bit int, but fits in 64-bit).
        (void)x;
        (void)y;
    }

    inf.readEof();
}
