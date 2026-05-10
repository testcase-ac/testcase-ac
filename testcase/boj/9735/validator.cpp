#include "testlib.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cassert>
using namespace std;

// Evaluate cubic f(x) = A*x^3 + B*x^2 + C*x + D by Horner's method
static long double eval_f(long double x, int A, int B, int C, int D) {
    return ((( (long double)A * x + B ) * x + C ) * x + D);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int N = inf.readInt(1, 99, "N");
    inf.readEoln();

    for (int tc = 1; tc <= N; tc++) {
        // Read coefficients
        int A = inf.readInt(-2000000, 2000000, "A");
        inf.readSpace();
        int B = inf.readInt(-2000000, 2000000, "B");
        inf.readSpace();
        int C = inf.readInt(-2000000, 2000000, "C");
        inf.readSpace();
        int D = inf.readInt(-2000000, 2000000, "D");
        inf.readEoln();

        // A must be non-zero
        ensuref(A != 0, "Equation %d: A must be non-zero, got A=0", tc);

        // Check that there is at least one integer root by rational root theorem:
        bool hasIntRoot = false;
        // If D == 0, x=0 is a root
        if (D == 0) {
            hasIntRoot = true;
        } else {
            // enumerate positive divisors of |D|
            int64_t absD = D < 0 ? -(int64_t)D : (int64_t)D;
            vector<int> divs;
            for (int64_t i = 1; i * i <= absD; i++) {
                if (absD % i == 0) {
                    divs.push_back((int)i);
                    if (i * i != absD)
                        divs.push_back((int)(absD / i));
                }
            }
            for (int d : divs) {
                if (hasIntRoot) break;
                // check +d
                {
                    __int128 t = 0;
                    t = (__int128)A * d;
                    t = t * d + B;
                    t = t * d + C;
                    t = t * d + D;
                    if (t == 0) { hasIntRoot = true; break; }
                }
                // check -d
                {
                    __int128 nd = - (int64_t)d;
                    __int128 t = 0;
                    t = (__int128)A * nd;
                    t = t * nd + B;
                    t = t * nd + C;
                    t = t * nd + D;
                    if (t == 0) { hasIntRoot = true; break; }
                }
            }
        }
        ensuref(hasIntRoot, "Equation %d: no integer root for coefficients (%d, %d, %d, %d)",
                tc, A, B, C, D);

        // Now compute all real roots by numeric method
        const long double LB = -2000001.0L, UB = 2000001.0L;
        vector<long double> roots;
        // Compute discriminant of derivative: f'(x) = 3A x^2 + 2B x + C
        long double disc = (long double)4 * B * B - (long double)12 * A * C;
        if (disc > 0) {
            // Two distinct critical points -> possible 3 real roots
            long double sq = sqrt(disc);
            long double x1 = ((long double)(-2) * B - sq) / ((long double)6 * A);
            long double x2 = ((long double)(-2) * B + sq) / ((long double)6 * A);
            if (x1 > x2) std::swap(x1, x2);
            // Three intervals: [LB, x1], [x1, x2], [x2, UB]
            vector<pair<long double,long double>> segs = {
                {LB, x1}, {x1, x2}, {x2, UB}
            };
            for (auto &sg : segs) {
                long double l = sg.first, r = sg.second;
                long double fl = eval_f(l, A, B, C, D);
                long double fr = eval_f(r, A, B, C, D);
                if (fl == 0) {
                    roots.push_back(l);
                } else if (fl * fr <= 0) {
                    // root in (l, r]
                    long double lo = l, hi = r;
                    // binary search
                    for (int it = 0; it < 60; it++) {
                        long double mid = (lo + hi) / 2;
                        long double fm = eval_f(mid, A, B, C, D);
                        if (fl * fm <= 0) {
                            hi = mid;
                            fr = fm;
                        } else {
                            lo = mid;
                            fl = fm;
                        }
                    }
                    roots.push_back((lo + hi) / 2);
                }
            }
        } else {
            // Only one real root
            long double fl = eval_f(LB, A, B, C, D);
            long double fr = eval_f(UB, A, B, C, D);
            ensuref(fl * fr <= 0,
                    "Equation %d: signs at LB and UB are same, fl=%.12Lf fr=%.12Lf", tc, fl, fr);
            long double lo = LB, hi = UB;
            for (int it = 0; it < 80; it++) {
                long double mid = (lo + hi) / 2;
                long double fm = eval_f(mid, A, B, C, D);
                if (fl * fm <= 0) {
                    hi = mid;
                    fr = fm;
                } else {
                    lo = mid;
                    fl = fm;
                }
            }
            roots.push_back((lo + hi) / 2);
        }

        // Sort and deduplicate within small eps
        sort(roots.begin(), roots.end());
        // After sort, there must be either 1 or 3 distinct roots
        ensuref(roots.size() >= 1 && roots.size() <= 3,
                "Equation %d: found %d real roots, expected 1 or 3", tc, (int)roots.size());

        // Validate bounds and separation
        const long double EPS_BOUND = 1e-7L;
        const long double MIN_DIFF = 1e-4L;
        for (size_t i = 0; i < roots.size(); i++) {
            long double x = roots[i];
            ensuref(x >= -1000000.0L - EPS_BOUND && x <= 1000000.0L + EPS_BOUND,
                    "Equation %d: root %.12Lf out of bounds [-1e6,1e6]", tc, (double)x);
            if (i + 1 < roots.size()) {
                long double diff = roots[i+1] - roots[i];
                ensuref(diff > MIN_DIFF - 1e-12L,
                        "Equation %d: roots too close: %.12Lf and %.12Lf (diff=%.12Lf)",
                        tc, (double)roots[i], (double)roots[i+1], (double)diff);
            }
        }
    }

    inf.readEof();
    return 0;
}
