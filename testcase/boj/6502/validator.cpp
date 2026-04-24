#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    int test_cnt = 0;
    while (true) {
        // Read r, which can be 0 (termination) or [1,1000]
        int r = inf.readInt(0, 1000, "r");
        if (r == 0) {
            // termination line must be exactly "0\n"
            inf.readEoln();
            break;
        }
        // Non-termination case: must have three numbers
        inf.readSpace();
        int w = inf.readInt(1, 1000, "w");
        inf.readSpace();
        int l = inf.readInt(1, 1000, "l");
        inf.readEoln();

        // Validate w <= l
        ensuref(w <= l,
                "At test case %d: width w = %d must be <= length l = %d", 
                test_cnt+1, w, l);
        // Count test cases
        test_cnt++;
        ensuref(test_cnt <= MAX_CASES,
                "Number of test cases (%d) exceeds limit %d",
                test_cnt, MAX_CASES);
    }

    inf.readEof();
    return 0;
}
