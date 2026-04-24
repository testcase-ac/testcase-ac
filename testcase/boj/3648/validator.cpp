#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    // Read multiple test cases until EOF
    while (!inf.eof()) {
        ++tc;
        setTestCase(tc);

        // Read n and m
        int n = inf.readInt(2, 999, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1999, "m");
        inf.readEoln();

        // For each judge, read two votes a and b
        for (int i = 1; i <= m; i++) {
            int a = inf.readInt(-n, n, "a");
            ensuref(a != 0,
                    "Case %d, judge %d: first vote must be non-zero, got 0", 
                    tc, i);
            inf.readSpace();
            int b = inf.readInt(-n, n, "b");
            ensuref(b != 0,
                    "Case %d, judge %d: second vote must be non-zero, got 0", 
                    tc, i);
            inf.readEoln();

            ensuref(abs(a) != abs(b),
                    "Case %d, judge %d: both votes refer to the same participant %d",
                    tc, i, abs(a));
        }
    }

    // There must be at least one test case
    ensuref(tc > 0, "No test cases found");

    inf.readEof();
    return 0;
}
