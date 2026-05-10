#include "testlib.h"
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

// Helper function to check if a string is a floating point number with exactly 6 digits after the decimal point
bool is_valid_fp(const string& s) {
    // Should be of the form: [0-9]+.[0-9]{6}
    int dot = s.find('.');
    if (dot == string::npos) return false;
    if (dot == 0 || dot == (int)s.size() - 1) return false;
    // Only one dot
    if (s.find('.', dot + 1) != string::npos) return false;
    // Before dot: digits, after dot: exactly 6 digits
    for (int i = 0; i < dot; ++i) {
        if (!isdigit(s[i])) return false;
    }
    if ((int)s.size() - dot - 1 != 6) return false;
    for (int i = dot + 1; i < (int)s.size(); ++i) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    vector<double> xs, ys;

    for (int i = 0; i < n; ++i) {
        // Read as tokens to check format
        string sx = inf.readToken("[^ ]+", "x");
        inf.readSpace();
        string sy = inf.readToken("[^ \n]+", "y");
        inf.readEoln();

        ensuref(is_valid_fp(sx), "x coordinate at line %d is not a floating point number with exactly 6 digits after decimal: '%s'", i+2, sx.c_str());
        ensuref(is_valid_fp(sy) || (sy[0] == '-' && is_valid_fp(sy.substr(1))), "y coordinate at line %d is not a floating point number with exactly 6 digits after decimal: '%s'", i+2, sy.c_str());

        double x = stod(sx);
        double y = stod(sy);

        ensuref(0.0 <= x && x <= 1.0, "x coordinate at line %d is out of bounds: %s", i+2, sx.c_str());
        ensuref(fabs(y) < 0.5, "y coordinate at line %d is out of bounds: %s", i+2, sy.c_str());

        xs.push_back(x);
        ys.push_back(y);
    }

    // Check first and last point
    ensuref(fabs(xs[0] - 0.0) <= 1e-8 && fabs(ys[0] - 0.0) <= 1e-8, "First point is not (0.000000, 0.000000)");
    ensuref(fabs(xs[n-1] - 1.0) <= 1e-8 && fabs(ys[n-1] - 0.0) <= 1e-8, "Last point is not (1.000000, 0.000000)");

    // Check that points are connected in order (polyline, no jumps)
    for (int i = 1; i < n; ++i) {
        // No explicit constraint on monotonicity or non-degeneracy, but polyline is a sequence of points
        // (no need to check for self-intersection, as problem guarantees "does not overlap with itself")
        // But we can check that all points are distinct (no zero-length segments)
        ensuref(!(fabs(xs[i] - xs[i-1]) <= 1e-8 && fabs(ys[i] - ys[i-1]) <= 1e-8),
            "Consecutive points %d and %d are identical: (%.6f, %.6f)", i, i+1, xs[i], ys[i]);
    }

    inf.readEof();
}
