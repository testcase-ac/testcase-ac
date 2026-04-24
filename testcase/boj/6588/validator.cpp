#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int count = 0;
    while (true) {
        // Read n in [0, 1e6], zero signals end
        int n = inf.readInt(0, 1000000, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }
        // Validate each test case
        ensuref(n >= 6, "Each n must be at least 6, found %d", n);
        ensuref(n % 2 == 0, "Each n must be even, found %d", n);
        count++;
        ensuref(count <= 100000, "Number of test cases exceeds 100000: %d", count);
    }
    // There must be at least one test case before the terminating 0
    ensuref(count >= 1, "At least one test case is required, found %d", count);

    inf.readEof();
    return 0;
}
