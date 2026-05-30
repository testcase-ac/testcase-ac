#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Maximum allowed N as string: 10^18
    const string MAXN = "1000000000000000000";

    for (int tc = 1; tc <= T; tc++) {
        // Read N as a token of digits
        string s = inf.readToken("[0-9]+", "N");

        // No leading zeros unless the number is exactly "0"
        // But problem states N is a positive integer, so "0" is not allowed at all.
        ensuref(s != "0",
                "N must be a positive integer (>=1) at test case %d, got '%s'", 
                tc, s.c_str());
        if (s.size() > 1) {
            ensuref(s[0] != '0',
                    "Leading zeros are not allowed in N at test case %d, got '%s'",
                    tc, s.c_str());
        }

        // Check the upper bound: N <= 10^21
        ensuref(s.size() <= MAXN.size(),
                "N has too many digits at test case %d, got '%s'",
                tc, s.c_str());
        if (s.size() == MAXN.size()) {
            ensuref(s <= MAXN,
                    "N is too large at test case %d, got '%s'",
                    tc, s.c_str());
        }

        // Each test case line must end exactly with a newline
        inf.readEoln();
    }

    // No extra data after the test cases
    inf.readEof();
    return 0;
}
