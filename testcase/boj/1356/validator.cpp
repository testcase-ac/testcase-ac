#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N as a token of digits
    string s = inf.readToken("[0-9]+", "N");
    // No leading zeros allowed (since natural numbers are given in usual decimal form)
    ensuref(s[0] != '0', "Leading zero in N: \"%s\"", s.c_str());
    // Parse and check range 1 <= N <= 2,147,483,647
    long long val = 0;
    for (char c : s) {
        int d = c - '0';
        val = val * 10 + d;
        ensuref(val <= 2147483647LL,
                "N should be at most 2147483647, but got %s", s.c_str());
    }
    ensuref(val >= 1LL, "N should be at least 1, but got %s", s.c_str());

    // Exactly one newline after the number, then EOF
    inf.readEoln();
    inf.readEof();

    return 0;
}
