#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Number of operations (allow 0 per statement's lack of lower bound)
        int k = inf.readInt(1, 1000000, "k");
        inf.readEoln();

        for (int i = 0; i < k; i++) {
            // Operation type: either 'I' or 'D'
            string op = inf.readToken("[ID]", "op");
            inf.readSpace();
            if (op == "I") {
                // Insert operation: value in range [-2^31, 2^31-1]
                long long v = inf.readLong(-2147483648LL, 2147483647LL, "n");
                (void)v;
            } else {
                // Delete operation: argument must be exactly 1 or -1
                int d = inf.readInt(-1, 1, "n");
                ensuref(d == 1 || d == -1,
                        "For 'D' operation, argument must be 1 or -1, found %d", d);
            }
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
