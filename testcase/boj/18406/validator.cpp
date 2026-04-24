#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the score as a token of digits
    string s = inf.readToken("[0-9]+", "N");
    // Check that the number of digits is between 2 and 8
    ensuref(s.size() >= 2 && s.size() <= 8,
            "The number of digits of N must be between 2 and 8, but got %d", (int)s.size());
    // Leading zero is not allowed for multi-digit number
    ensuref(s[0] != '0',
            "Leading zeros are not allowed in N, but got \"%s\"", s.c_str());
    // The number of digits must be even
    ensuref(s.size() % 2 == 0,
            "The number of digits of N must be even, but got %d", (int)s.size());

    // Parse into integer and check bounds 10 <= N <= 99999999
    long long N = 0;
    for (char c : s) {
        N = N * 10 + (c - '0');
    }
    ensuref(N >= 10 && N <= 99999999LL,
            "N must be between 10 and 99999999, but got %lld", N);

    // End of line and EOF
    inf.readEoln();
    inf.readEof();

    return 0;
}
