#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    int case_cnt = 0;
    while (true) {
        // Read N, allow 0 for termination
        int N = inf.readInt(0, 25, "N");
        if (N == 0) {
            // termination line must be exactly "0\n"
            inf.readEoln();
            break;
        }
        // it's a real test case
        case_cnt++;
        ensuref(case_cnt <= MAX_CASES,
                "Number of test cases exceeds limit (%d)", MAX_CASES);

        // After N, there must be a space before the sequence
        inf.readSpace();
        // Read the N guesses, each between 1 and 99
        inf.readInts(N, 1, 99, "x_i");
        // End of this test case line
        inf.readEoln();
    }

    // No extra content after the 0 line
    inf.readEof();
    return 0;
}
