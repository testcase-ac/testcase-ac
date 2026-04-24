#include "testlib.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <cctype>

using namespace std;

// Check that the string is a valid decimal number with at most 3 decimal places
bool validDoubleFormat(const string &s) {
    int n = (int)s.size();
    if (n == 0) return false;
    int i = 0;
    // optional sign
    if (s[i] == '+' || s[i] == '-') i++;
    // at least one digit before decimal point
    int cntInt = 0;
    while (i < n && isdigit(s[i])) {
        cntInt++; i++;
    }
    if (cntInt == 0) return false;
    // optional fractional part
    if (i < n && s[i] == '.') {
        i++;
        int cntFrac = 0;
        while (i < n && isdigit(s[i])) {
            cntFrac++; i++;
        }
        if (cntFrac == 0 || cntFrac > 3) return false;
    }
    // no other characters
    return (i == n);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, S, V
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readSpace();
    int S = inf.readInt(1, 100, "S");
    inf.readSpace();
    int V = inf.readInt(1, 100, "V");
    inf.readEoln();

    // Read N mouse coordinates
    for (int i = 0; i < N; i++) {
        // read tokens (non-whitespace)
        string xs = inf.readToken("[^]+", "x_i");
        inf.readSpace();
        string ys = inf.readToken("[^]+", "y_i");
        inf.readEoln();

        // validate format
        ensuref(validDoubleFormat(xs),
                "Mouse %d: invalid x-coordinate format '%s'", i+1, xs.c_str());
        ensuref(validDoubleFormat(ys),
                "Mouse %d: invalid y-coordinate format '%s'", i+1, ys.c_str());
        // convert and check range
        double x = strtod(xs.c_str(), NULL);
        double y = strtod(ys.c_str(), NULL);
        ensuref(fabs(x) <= 1000.0 + 1e-9,
                "Mouse %d: x-coordinate out of range: %f", i+1, x);
        ensuref(fabs(y) <= 1000.0 + 1e-9,
                "Mouse %d: y-coordinate out of range: %f", i+1, y);
    }

    // Read M tunnel coordinates
    for (int i = 0; i < M; i++) {
        string xs = inf.readToken("[^]+", "x_j");
        inf.readSpace();
        string ys = inf.readToken("[^]+", "y_j");
        inf.readEoln();

        ensuref(validDoubleFormat(xs),
                "Tunnel %d: invalid x-coordinate format '%s'", i+1, xs.c_str());
        ensuref(validDoubleFormat(ys),
                "Tunnel %d: invalid y-coordinate format '%s'", i+1, ys.c_str());
        double x = strtod(xs.c_str(), NULL);
        double y = strtod(ys.c_str(), NULL);
        ensuref(fabs(x) <= 1000.0 + 1e-9,
                "Tunnel %d: x-coordinate out of range: %f", i+1, x);
        ensuref(fabs(y) <= 1000.0 + 1e-9,
                "Tunnel %d: y-coordinate out of range: %f", i+1, y);
    }

    // No extra data
    inf.readEof();
    return 0;
}
