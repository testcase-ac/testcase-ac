#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    // K must be at least 1 and strictly less than N
    int K = inf.readInt(1, N - 1, "K");
    inf.readEoln();

    // Read the N-digit number: no spaces, all digits, length exactly N, not starting with '0'
    string s = inf.readToken("[0-9]+", "number");
    inf.readEoln();

    ensuref((int)s.size() == N,
            "Length of number (%d) does not match N (%d)", (int)s.size(), N);
    ensuref(s[0] != '0',
            "Number must not start with '0', but got '%c' at position 1", s[0]);

    // All characters should be digits (the regex already enforces this, but double-check)
    for (int i = 0; i < N; i++) {
        char c = s[i];
        ensuref(c >= '0' && c <= '9',
                "Invalid character '%c' at position %d: must be a digit", c, i + 1);
    }

    inf.readEof();
    return 0;
}
