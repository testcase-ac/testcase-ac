#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        string s = inf.readLine("[01]{1,200000}", "bit_string");

        // Check length explicitly (since regex is greedy, but let's be sure)
        int n = int(s.size());
        ensuref(1 <= n && n <= 200000, 
            "Test case #%d: Length of bit string is %d, but must be in [1, 200000]", tc, n);

        // Check all characters are '0' or '1'
        for (int i = 0; i < n; ++i) {
            ensuref(s[i] == '0' || s[i] == '1',
                "Test case #%d: Invalid character at position %d: '%c' (must be '0' or '1')", tc, i+1, s[i]);
        }
    }

    inf.readEof();
}
