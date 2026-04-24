#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // According to the problem, each line has one integer n0,
    // where 0 < n0 < 1,000,000, and input terminates with a line "0".
    int case_count = 0;
    while (true) {
        // We allow 0 for the sentinel, and up to 999999 for real cases.
        int n0 = inf.readInt(0, 999999, "n0");
        inf.readEoln();

        if (n0 == 0) {
            // End of all test cases
            break;
        }
        // For actual test cases, enforce 1 <= n0 < 1,000,000
        ensuref(n0 >= 1 && n0 < 1000000,
                "Each n0 must satisfy 1 <= n0 < 1000000, got %d", n0);
        case_count++;
    }

    // Implicit limit on number of test cases if not stated: 100,000
    ensuref(case_count <= 100000,
            "Number of test cases %d exceeds the limit of 100000", case_count);

    inf.readEof();
    return 0;
}
