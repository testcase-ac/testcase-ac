#include "testlib.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Helper to check if a floating point number is finite and not NaN
bool is_valid_float(double x) {
    return std::isfinite(x);
}

// Helper to check if a vector is non-zero
bool is_nonzero_vec(const vector<double>& v) {
    double norm = 0.0;
    for (double x : v) norm += x * x;
    return norm > 1e-12;
}

// Helper to check if two vectors are perpendicular (dot product == 0)
bool is_perpendicular(const vector<double>& a, const vector<double>& b) {
    double dot = 0.0;
    for (int i = 0; i < 3; ++i) dot += a[i] * b[i];
    return std::abs(dot) <= 1e-8;
}

// Helper to check if two vectors are linearly independent
bool is_linearly_independent(const vector<double>& a, const vector<double>& b) {
    // If a and b are both nonzero and not colinear, they are linearly independent
    double norm_a = 0.0, norm_b = 0.0;
    for (int i = 0; i < 3; ++i) {
        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }
    if (norm_a < 1e-12 || norm_b < 1e-12) return false;
    // Check if cross product is nonzero
    double cx = a[1]*b[2] - a[2]*b[1];
    double cy = a[2]*b[0] - a[0]*b[2];
    double cz = a[0]*b[1] - a[1]*b[0];
    double norm_c = cx*cx + cy*cy + cz*cz;
    return norm_c > 1e-12;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // 2. Read h1 h2 h3
    vector<double> h(3);
    for (int i = 0; i < 3; ++i) {
        h[i] = inf.readDouble(-10.0, 10.0, ("h_" + to_string(i+1)).c_str());
        if (i < 2) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read v1 v2 v3
    vector<double> v(3);
    for (int i = 0; i < 3; ++i) {
        v[i] = inf.readDouble(-10.0, 10.0, ("v_" + to_string(i+1)).c_str());
        if (i < 2) inf.readSpace();
    }
    inf.readEoln();

    // 4. Validate h and v are nonzero, perpendicular, and linearly independent
    ensuref(is_nonzero_vec(h), "h vector is zero vector");
    ensuref(is_nonzero_vec(v), "v vector is zero vector");
    ensuref(is_perpendicular(h, v), "h and v vectors are not perpendicular");
    ensuref(is_linearly_independent(h, v), "h and v vectors are not linearly independent");

    // 5. Read n lines of darts
    for (int i = 0; i < n; ++i) {
        // p1 p2 p3
        for (int j = 0; j < 3; ++j) {
            double p = inf.readDouble(-100.0, 100.0, ("p_" + to_string(j+1)).c_str());
            if (j < 2) inf.readSpace();
            else inf.readSpace();
        }
        // d1 d2 d3
        vector<double> d(3);
        for (int j = 0; j < 3; ++j) {
            d[j] = inf.readDouble(-10.0, 10.0, ("d_" + to_string(j+1)).c_str());
            if (j < 2) inf.readSpace();
        }
        inf.readEoln();
        ensuref(is_nonzero_vec(d), "Direction vector d is zero at dart %d", i+1);
    }

    inf.readEof();
}
