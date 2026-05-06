#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Read a fixed-point decimal with exactly two digits after the decimal point,
// in canonical form, and ensure its numeric value is within [lo, hi].
double readFixed2(double lo, double hi, const char* name) {
    string s = inf.readToken("[^ ]+", name);

    // Canonical form:
    //  - optional single leading '-'
    //  - integer part: "0" or non-zero without leading zeros
    //  - a dot '.'
    //  - exactly two digits
    //
    // Regex explanation:
    //   ^-?           optional '-'
    //   (0|[1-9][0-9]*)  "0" or non-zero without leading zeros
    //   \.            decimal point
    //   [0-9]{2}$     exactly two digits after decimal
    static const regex re("^(-?(0|[1-9][0-9]*))\\.[0-9]{2}$");
    ensuref(regex_match(s, re),
            "%s must be a decimal number with exactly two digits after decimal and no leading zeros: got '%s'",
            name, s.c_str());

    // Parse as integer cents to avoid floating-point issues and check bounds exactly
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

    long long loC = llround(lo * 100.0);
    long long hiC = llround(hi * 100.0);

    ensuref(cents >= loC && cents <= hiC,
            "%s = %s out of range [%.2f, %.2f]",
            name, s.c_str(), lo, hi);

    return cents / 100.0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T: 1 ≤ T ≤ 20
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // First line of test case: N A B
        // The "Limits" section says N = 1, but the sample has N = 2.
        // To support both, we validate 1 ≤ N ≤ 100000 and then enforce
        // the other stated constraints (ranges on coordinates, distinct C_i).
        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        double A = readFixed2(-10.00, 10.00, "A");
        inf.readSpace();
        double B = readFixed2(-10.00, 10.00, "B");
        inf.readEoln();

        // Second line: N floating-point numbers C_i
        vector<double> C(N);
        for (int i = 0; i < N; ++i) {
            C[i] = readFixed2(-10.00, 10.00, "C_i");
            if (i + 1 < N) inf.readSpace();
        }
        inf.readEoln();

        // Check C_i are distinct.
        // They all have exactly two decimals, so direct comparison is safe.
        sort(C.begin(), C.end());
        for (int i = 1; i < N; ++i) {
            ensuref(C[i] != C[i - 1],
                    "C_i must be distinct, but two islands share coordinate %.2f",
                    C[i]);
        }

        // No additional global geometric / path properties are guaranteed by the
        // statement that must be enforced at input level: feasibility of a safe
        // path and the optimization over paths are responsibilities of solutions,
        // not of the validator.
    }

    inf.readEof();
}
