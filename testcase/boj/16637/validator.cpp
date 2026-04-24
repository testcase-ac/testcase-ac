#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: length of the expression
    int N = inf.readInt(1, 19, "N");
    // N must be odd
    ensuref(N % 2 == 1, "N must be odd, but N = %d", N);
    inf.readEoln();

    // Read the expression as one token (no spaces allowed)
    string s = inf.readToken("[^]+", "expression");
    // It must end exactly at length N
    ensuref((int)s.size() == N,
            "Length of expression (%d) does not match N (%d)", (int)s.size(), N);
    // Validate alternation: digit, operator, digit, ...
    for (int i = 0; i < N; i++) {
        char c = s[i];
        if (i % 2 == 0) {
            // even index: digit 0-9
            ensuref(c >= '0' && c <= '9',
                    "Expected digit at position %d but found '%c'", i, c);
        } else {
            // odd index: operator +, -, *
            ensuref(c == '+' || c == '-' || c == '*',
                    "Expected operator (+, -, *) at position %d but found '%c'", i, c);
        }
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}
