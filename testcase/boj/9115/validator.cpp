#include "testlib.h"

#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for the number of test cases.
    int testCases = inf.readInt(1, 100000, "testCases");
    inf.readEoln();

    for (int tc = 1; tc <= testCases; ++tc) {
        setTestCase(tc);

        int a = inf.readInt(2, 10000, "a");
        inf.readSpace();
        int b = inf.readInt(2, 10000, "b");
        inf.readSpace();
        int c = inf.readInt(2, 10000, "c");
        inf.readSpace();
        int d = inf.readInt(2, 10000, "d");
        inf.readEoln();

        int g = gcd(gcd(a, b), gcd(c, d));
        ensuref(g == 1, "gcd(a, b, c, d) must be 1, found %d", g);
    }

    inf.readEof();
}
