#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int test_cases = 0;
    while (true) {
        // Read the line containing n as a token of digits
        string n_token = inf.readToken("[0-9]+", "n");
        inf.readEoln();

        // No leading zeros allowed (except the single "0")
        if (n_token.size() > 1) {
            ensuref(n_token[0] != '0',
                    "Leading zeros in n: \"%s\"", n_token.c_str());
        }
        // n_token should have at most 4 digits since max n is 1000
        ensuref(n_token.size() <= 4,
                "n has too many digits: \"%s\"", n_token.c_str());

        // Parse n and check bounds 0 <= n <= 1000
        int n = 0;
        for (char c : n_token) {
            n = n * 10 + (c - '0');
        }
        ensuref(0 <= n && n <= 1000,
                "n is out of bounds: %d (expected 0 to 1000)", n);

        // If n == 0, this is the terminator
        if (n == 0) break;

        // Count test cases and enforce a reasonable upper bound
        test_cases++;
        ensuref(test_cases <= 100000,
                "Too many test cases: %d (maximum allowed is 100000)", test_cases);

        // Read n lines of text
        for (int i = 0; i < n; i++) {
            // Read entire line (may contain spaces)
            string line = inf.readLine("[^]*", "line");
            int len = (int)line.size();
            // Check line length 1..100
            ensuref(1 <= len && len <= 100,
                    "Length of line %d in test case %d is %d (expected 1 to 100)",
                    i+1, test_cases, len);
            // Check each character is printable ASCII (32..126)
            for (int j = 0; j < len; j++) {
                unsigned char c = line[j];
                int code = (int)c;
                ensuref(32 <= code && code <= 126,
                        "Invalid character code %d in line %d of test case %d at position %d",
                        code, i+1, test_cases, j+1);
            }
        }
    }

    inf.readEof();
    return 0;
}
