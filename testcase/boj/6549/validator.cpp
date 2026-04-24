#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int test_count = 0;
    while (true) {
        // Read the number of bars n; 0 marks the end of input.
        int n = inf.readInt(0, 100000, "n");
        // After n, there must be exactly a newline if n == 0, or a space then heights if n > 0.
        if (n == 0) {
            inf.readEoln();
            break;
        }
        test_count++;
        // Read the heights
        inf.readSpace();
        vector<long long> h = inf.readLongs(n, 0LL, 1000000000LL, "h_i");
        inf.readEoln();
    }

    // Enforce assumed limit on number of test cases
    ensuref(test_count <= 100000,
            "Number of test cases (%d) exceeds limit of 100000", test_count);

    inf.readEof();
    return 0;
}
