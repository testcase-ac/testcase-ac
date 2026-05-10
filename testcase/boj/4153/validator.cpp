#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Count of non-terminating test cases
    int tc_count = 0;
    while (true) {
        // Read three integers per line: allow 0 (for terminator) up to 30000
        int a = inf.readInt(0, 30000, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, 30000, "b_i");
        inf.readSpace();
        int c = inf.readInt(0, 30000, "c_i");
        inf.readEoln();

        // Terminator line
        if (a == 0 && b == 0 && c == 0) {
            break;
        }

        // For actual test cases, sides must be positive and < 30000
        ensuref(a > 0 && a < 30000,
                "Side length a_i = %d is out of bounds [1,29999]", a);
        ensuref(b > 0 && b < 30000,
                "Side length b_i = %d is out of bounds [1,29999]", b);
        ensuref(c > 0 && c < 30000,
                "Side length c_i = %d is out of bounds [1,29999]", c);

        // Limit on number of test cases (unspecified in statement => up to 1e5)
        ++tc_count;
        ensuref(tc_count <= 100000,
                "Number of test cases %d exceeds maximum of 100000", tc_count);
    }

    inf.readEof();
    return 0;
}
