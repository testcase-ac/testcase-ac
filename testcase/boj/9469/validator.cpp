#include "testlib.h"
#include <string>
#include <cctype>
#include <cstdlib>
#include <cmath>
using namespace std;

// Check that s is a non-negative decimal number with at most two fractional digits,
// at least one digit before decimal, and if decimal point present, 1-2 digits after.
void checkDecimalFormat(const string &s, const char *name) {
    ensuref(!s.empty(), "%s: empty string", name);
    int dots = 0;
    int n = (int)s.size();
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '.') {
            dots++;
        } else {
            ensuref(isdigit(c), "%s: invalid character '%c' in \"%s\"", name, c, s.c_str());
        }
    }
    ensuref(dots <= 1, "%s: more than one decimal point in \"%s\"", name, s.c_str());
    if (dots == 1) {
        int p = (int)s.find('.');
        // at least one digit before '.'
        ensuref(p >= 1, "%s: no digit before decimal point in \"%s\"", name, s.c_str());
        int frac = n - p - 1;
        ensuref(frac >= 1 && frac <= 2,
                "%s: must have 1 or 2 digits after decimal point in \"%s\"", name, s.c_str());
    }
    // no leading '+' or '-'
    ensuref(s[0] != '+' && s[0] != '-',
            "%s: leading sign not allowed in \"%s\"", name, s.c_str());
}

// Parse a decimal string to long double, assume format already checked
long double parseDec(const string &s) {
    // stold will accept our format
    return stold(s);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int i = 0; i < P; i++) {
        // N: test case number, must equal i+1
        int N = inf.readInt(1, P, "N");
        ensuref(N == i+1,
                "Test case number N must be %d but got %d", i+1, N);
        inf.readSpace();

        // D: rail length
        string D_str = inf.readToken("[^ ]+", "D");
        checkDecimalFormat(D_str, "D");
        long double D = parseDec(D_str);
        ensuref(D >= 10.0L && D <= 1000.0L,
                "D must be in [10,1000], but got %Lf (from \"%s\")",
                D, D_str.c_str());
        inf.readSpace();

        // A: speed of train A
        string A_str = inf.readToken("[^ ]+", "A");
        checkDecimalFormat(A_str, "A");
        long double A = parseDec(A_str);
        ensuref(A >= 1.0L && A <= 40.0L,
                "A must be in [1,40], but got %Lf (from \"%s\")",
                A, A_str.c_str());
        inf.readSpace();

        // B: speed of train B
        string B_str = inf.readToken("[^ ]+", "B");
        checkDecimalFormat(B_str, "B");
        long double B = parseDec(B_str);
        ensuref(B >= 1.0L && B <= 40.0L,
                "B must be in [1,40], but got %Lf (from \"%s\")",
                B, B_str.c_str());
        // ensure A <= B
        ensuref(A <= B,
                "A must be <= B, but got A=%Lf and B=%Lf", A, B);
        inf.readSpace();

        // F: speed of fly
        string F_str = inf.readToken("[^ ]+", "F");
        checkDecimalFormat(F_str, "F");
        long double F = parseDec(F_str);
        ensuref(F > B,
                "F must be > B, but got F=%Lf and B=%Lf", F, B);
        ensuref(F <= 50.0L,
                "F must be <= 50, but got %Lf (from \"%s\")",
                F, F_str.c_str());

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
