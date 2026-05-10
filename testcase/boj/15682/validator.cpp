#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Solve cubic equation A*x^3 + B*x^2 + C*x + D = 0 for real roots
vector<long double> solveCubic(long double A, long double B, long double C, long double D) {
    // normalize: x = t - b/3
    long double b = B / A;
    long double c = C / A;
    long double d = D / A;
    long double bb = b * b;
    long double p = c - bb / 3.0L;
    long double q = 2.0L * b * bb / 27.0L - b * c / 3.0L + d;
    long double halfq = q / 2.0L;
    long double thirdp = p / 3.0L;
    long double discr = halfq * halfq + thirdp * thirdp * thirdp;
    const long double EPS_D = 1e-18L;
    vector<long double> res;
    if (discr > EPS_D) {
        // one real root
        long double sq = sqrt(discr);
        long double u = cbrt(-halfq + sq);
        long double v = cbrt(-halfq - sq);
        long double t = u + v;
        res.push_back(t - b / 3.0L);
    } else if (fabsl(discr) <= EPS_D) {
        // multiple roots: double or triple
        long double u = cbrt(-halfq);
        // roots: t1 = 2u, t2 = -u
        res.push_back(2.0L * u - b / 3.0L);
        res.push_back(-u - b / 3.0L);
    } else {
        // three distinct real roots
        long double rho = sqrt(-thirdp * thirdp * thirdp);
        long double phi = acos(max((long double)-1.0L, min((long double)1.0L, -halfq / rho)));
        long double r = 2.0L * sqrt(-thirdp);
        long double t1 = r * cos(phi / 3.0L);
        long double t2 = r * cos((phi + 2.0L * M_PI) / 3.0L);
        long double t3 = r * cos((phi + 4.0L * M_PI) / 3.0L);
        res.push_back(t1 - b / 3.0L);
        res.push_back(t2 - b / 3.0L);
        res.push_back(t3 - b / 3.0L);
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 0 < N < 100
    int N = inf.readInt(1, 99, "N");
    inf.readEoln();

    for (int tc = 1; tc <= N; tc++) {
        // Read four coefficients A, B, C, D as tokens (no spaces inside)
        string sA = inf.readToken("[^ ]+", "A");
        inf.readSpace();
        string sB = inf.readToken("[^ ]+", "B");
        inf.readSpace();
        string sC = inf.readToken("[^ ]+", "C");
        inf.readSpace();
        string sD = inf.readToken("[^ ]+", "D");
        inf.readEoln();

        // Helper to parse and validate a coefficient string
        auto parseCoeff = [&](const string &s, const char *name) {
            int pos = 0, len = s.size();
            // optional sign
            if (pos < len && (s[pos] == '+' || s[pos] == '-')) {
                pos++;
                ensuref(pos < len, "%s: missing digits after sign", name);
            }
            // at least one digit
            ensuref(pos < len && isdigit(s[pos]), "%s: must start with a digit", name);
            // integer part
            while (pos < len && isdigit(s[pos])) pos++;
            // optional fractional part
            if (pos < len && s[pos] == '.') {
                pos++;
                int start = pos;
                while (pos < len && isdigit(s[pos])) pos++;
                int fracLen = pos - start;
                ensuref(fracLen >= 1 && fracLen <= 11,
                        "%s: fractional part length must be between 1 and 11, got %d", name, fracLen);
            }
            ensuref(pos == len, "%s: invalid character '%c'", name, s[pos]);
            // parse to long double
            char *endptr = nullptr;
            long double val = strtold(s.c_str(), &endptr);
            ensuref(endptr && *endptr == '\0', "%s: cannot parse to long double", name);
            // range check [-2e6, 2e6]
            const long double LIM = 2000000.0L;
            ensuref(val >= -LIM - 1e-12L && val <= LIM + 1e-12L,
                    "%s: value %.15Lf out of range [-2000000,2000000]", name, val);
            return val;
        };

        long double A = parseCoeff(sA, "A");
        long double B = parseCoeff(sB, "B");
        long double C = parseCoeff(sC, "C");
        long double D = parseCoeff(sD, "D");

        // A must be non-zero
        ensuref(fabsl(A) > 1e-15L, "A must be non-zero");

        // Solve for real roots
        vector<long double> roots = solveCubic(A, B, C, D);
        // Sort roots
        sort(roots.begin(), roots.end());
        // Cluster into distinct roots: difference > 1e-9
        vector<long double> distinct;
        const long double EPS_ROOT = 1e-9L;
        for (long double x : roots) {
            if (distinct.empty() || x - distinct.back() > EPS_ROOT)
                distinct.push_back(x);
        }
        // Check that the clustered roots obey the separation guarantee
        for (size_t i = 1; i < distinct.size(); i++) {
            long double d = distinct[i] - distinct[i-1];
            ensuref(d > EPS_ROOT,
                    "Case %d: distinct roots %.12Lf and %.12Lf too close (diff=%.12Lf)",
                    tc, distinct[i-1], distinct[i], d);
        }
        // Each real root must be within [-1e6, 1e6]
        for (size_t i = 0; i < distinct.size(); i++) {
            long double x = distinct[i];
            ensuref(x >= -1000000.0L - 1e-6L && x <= 1000000.0L + 1e-6L,
                    "Case %d: root %.12Lf out of bounds [-1e6,1e6]", tc, x);
        }
        // At least one integer root (within 1e-6)
        bool hasInt = false;
        for (long double x : distinct) {
            long double r = roundl(x);
            if (fabsl(x - r) <= 1e-6L) {
                hasInt = true;
                break;
            }
        }
        ensuref(hasInt, "Case %d: no integer root found", tc);
    }

    inf.readEof();
    return 0;
}
