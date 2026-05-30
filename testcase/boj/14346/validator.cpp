#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Read a canonical fixed-point decimal with exactly two digits after the
// decimal point and return the value in cents.
int readFixed2(int lo, int hi, const char* name) {
    string s = inf.readToken("[^ ]+", name);

    static const regex re("^(-?(0|[1-9][0-9]*))\\.[0-9]{2}$");
    ensuref(regex_match(s, re),
            "%s must be a decimal number with exactly two digits after decimal and no leading zeros: got '%s'",
            name, s.c_str());

    bool neg = (s[0] == '-');
    string t = s;
    if (neg) t = t.substr(1);

    size_t pos = t.find('.');
    string intPart = t.substr(0, pos);
    string fracPart = t.substr(pos + 1); // exactly two digits, guaranteed by regex

    long long intVal = 0;
    for (char c : intPart) {
        intVal = intVal * 10 + (c - '0');
        // Safety guard, problem constraints are tiny but avoid crazy values
        ensuref(intVal <= (long long)1e9,
                "%s integer part too large in '%s'", name, s.c_str());
    }

    long long fracVal = 0;
    for (char c : fracPart) {
        fracVal = fracVal * 10 + (c - '0');
    }

    long long cents = intVal * 100 + fracVal;
    if (neg) cents = -cents;

    ensuref(cents >= lo && cents <= hi,
            "%s = %s out of range [%.2f, %.2f]",
            name, s.c_str(), lo / 100.0, hi / 100.0);

    return (int)cents;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T: 1 ≤ T ≤ 20
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // First line of test case: N A B.
        // CHECK: The unjudged sample includes N = 2, but this Small statement's
        // official input limit is N = 1.
        int N = inf.readInt(1, 1, "N");
        inf.readSpace();
        readFixed2(-1000, 1000, "A");
        inf.readSpace();
        readFixed2(-1000, 1000, "B");
        inf.readEoln();

        // Second line: N floating-point numbers C_i
        vector<int> C(N);
        for (int i = 0; i < N; ++i) {
            C[i] = readFixed2(-1000, 1000, "C_i");
            if (i + 1 < N) inf.readSpace();
        }
        inf.readEoln();

        // Check C_i are distinct.
        // They all have exactly two decimals, so direct comparison is safe.
        sort(C.begin(), C.end());
        for (int i = 1; i < N; ++i) {
            ensuref(C[i] != C[i - 1],
                    "C_i must be distinct, but two islands share coordinate %.2f",
                    C[i] / 100.0);
        }

        // No additional global geometric / path properties are guaranteed by the
        // statement that must be enforced at input level: feasibility of a safe
        // path and the optimization over paths are responsibilities of solutions,
        // not of the validator.
    }

    inf.readEof();
}
