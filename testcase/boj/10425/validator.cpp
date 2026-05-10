#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Each test case: a positive integer Fn
    for (int tc = 0; tc < T; tc++) {
        // Read Fn as a token of digits
        string s = inf.readToken("[0-9]+", "Fn");
        inf.readEoln();

        // No leading zeros (and Fn >= 1)
        ensuref(s[0] != '0',
                "Leading zero in Fn (test case %d): \"%s\"", tc+1, s.c_str());

        int L = (int)s.size();
        // Fn must be <= 10^21000, i.e., at most 21001 digits, and if 21001, it must be exactly "1" followed by 21000 zeros
        const int MAX_LEN = 21001;
        ensuref(L <= MAX_LEN,
                "Length of Fn in test case %d is %d, exceeding maximum %d",
                tc+1, L, MAX_LEN);

        if (L == MAX_LEN) {
            // Must be exactly 10^21000
            ensuref(s[0] == '1',
                    "Fn of length %d in test case %d must start with '1', got '%c'",
                    L, tc+1, s[0]);
            for (int i = 1; i < L; i++) {
                if (s[i] != '0') {
                    ensuref(false,
                            "Fn of length %d in test case %d must be 10^21000 but char %d is '%c'",
                            L, tc+1, i+1, s[i]);
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
