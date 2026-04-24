#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int test_cases = 0;
    while (true) {
        // Read one line of three integers
        int a = inf.readInt(-50, 50, "a");
        inf.readSpace();
        int b = inf.readInt(-50, 50, "b");
        inf.readSpace();
        int c = inf.readInt(-50, 50, "c");
        inf.readEoln();

        // Check for terminator
        if (a == -1 && b == -1 && c == -1) {
            break;
        }
        // Count valid queries
        test_cases++;
    }

    // By problem rules, number of test cases not specified => assume ≤ 100000
    ensuref(test_cases <= 100000,
            "Number of test cases %d exceeds limit of 100000", test_cases);

    inf.readEof();
    return 0;
}
