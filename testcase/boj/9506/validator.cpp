#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCount = 0;
    // Each line contains one integer n. Terminate on n = -1.
    while (true) {
        // We allow -1 as the sentinel, or [3, 99999] for valid test cases.
        int n = inf.readInt(-1, 99999, "n");
        inf.readEoln();

        if (n == -1) {
            // End of input marker
            break;
        }
        // Validate problem constraint: 2 < n < 100000
        ensuref(n > 2,
                "Each n must satisfy 2 < n < 100000, but found n = %d", n);

        // No more than 100000 test cases (implicit limit)
        ++testCount;
        ensuref(testCount <= 100000,
                "Too many test cases: %d (maximum is 100000)", testCount);
    }

    inf.readEof();
    return 0;
}
