#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n (teams) and m (matches)
        int n = inf.readInt(2, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(2, 1000, "m");
        inf.readEoln();

        // Read each match
        for (int i = 1; i <= m; i++) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readSpace();
            // Teams must be distinct
            ensuref(a != b,
                    "In test %d, match %d: teams must be distinct but got a=%d, b=%d",
                    tc, i, a, b);

            int p = inf.readInt(0, 20, "p");
            inf.readSpace();
            int q = inf.readInt(0, 20, "q");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
