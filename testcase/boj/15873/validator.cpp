#include "testlib.h"
#include <string>
#include <cstdint>
using namespace std;

static int toInt(const string &s) {
    // s is guaranteed non-empty and all digits
    int x = 0;
    for (char c : s) {
        // prevent overflow (we only expect numbers up to 10 anyway)
        x = x * 10 + (c - '0');
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input line: a concatenation of A and B without spaces
    string s = inf.readToken("[0-9]+", "input");
    inf.readEoln();

    // Length must be between 2 and 4 (A and B each have 1 or 2 digits)
    int n = (int)s.size();
    ensuref(n >= 2 && n <= 4,
            "The total length of the input must be between 2 and 4 digits, found %d", n);

    // Try all splits into prefix A and suffix B
    int valid_splits = 0;
    for (int i = 1; i < n; i++) {
        string A = s.substr(0, i);
        string B = s.substr(i);
        // No leading zeros allowed when length > 1
        if ((A.size() > 1 && A[0] == '0') || (B.size() > 1 && B[0] == '0'))
            continue;
        int a = toInt(A);
        int b = toInt(B);
        // Both must satisfy 1 <= val <= 10
        if (a >= 1 && a <= 10 && b >= 1 && b <= 10) {
            valid_splits++;
        }
    }

    // There must be at least one valid way to interpret the input as A and B
    ensuref(valid_splits >= 1,
            "The input \"%s\" cannot be split into A and B with 1 <= A,B <= 10 without leading zeros",
            s.c_str());

    inf.readEof();
    return 0;
}
