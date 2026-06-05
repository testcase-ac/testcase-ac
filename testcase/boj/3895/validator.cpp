#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        int n = inf.readInt(0, 10000, "n");
        inf.readSpace();
        int k = inf.readInt(0, 10000, "k");
        inf.readSpace();
        int m = inf.readInt(0, 10000, "m");
        inf.readEoln();

        if (n == 0 && k == 0 && m == 0) {
            break;
        }

        ++cases;
        setTestCase(cases);
        ensuref(cases < 100, "number of data rows must be less than 100");
        ensuref(2 <= n && n <= 10000, "n out of range: %d", n);
        ensuref(1 <= k && k <= 10000, "k out of range: %d", k);
        ensuref(1 <= m && m <= n, "m out of range: %d for n=%d", m, n);
    }

    ensuref(cases > 0, "at least one data row is required before terminator");
    inf.readEof();
    return 0;
}
