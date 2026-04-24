#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        // Read N_i or the terminating 0
        int N = inf.readInt(0, 30, "N");
        inf.readEoln();
        if (N == 0) break;             // sentinel: end of input
        cases++;
        // Validate constraints for each test case
        ensuref(N >= 1,
                "Test case %d: N must be at least 1, found %d",
                cases, N);
        ensuref(N <= 30,
                "Test case %d: N must be at most 30, found %d",
                cases, N);
        // Check overall test case limit
        ensuref(cases <= 1000,
                "Number of test cases exceeds 1000: found %d",
                cases);
    }

    // No extra content after the terminating 0 line
    inf.readEof();
    return 0;
}
