#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size hyperparameter: small [2,5] or medium [6,12]
    bool small = rnd.next() < 0.7;
    int lo = small ? 2 : 6;
    int hi = small ? 5 : 12;

    // Value upper bound hyperparameter (always >=5)
    double pv = rnd.next();
    int ub;
    if (pv < 0.2) ub = 5;
    else if (pv < 0.6) ub = 100;
    else ub = 999;

    // Corridor scenario (2 x N or N x 2)
    bool corridor = rnd.next() < 0.15;
    int R, C;
    if (corridor) {
        bool rowCorr = rnd.next() < 0.5;
        if (rowCorr) {
            R = 2;
            C = rnd.next(lo, hi);
        } else {
            C = 2;
            R = rnd.next(lo, hi);
        }
    } else {
        // Parity scenarios
        double p = rnd.next();
        if (p < 0.25) {
            // both odd
            do { R = rnd.next(lo, hi); } while (R % 2 == 0);
            do { C = rnd.next(lo, hi); } while (C % 2 == 0);
        } else if (p < 0.5) {
            // R odd, C even
            do { R = rnd.next(lo, hi); } while (R % 2 == 0);
            do { C = rnd.next(lo, hi); } while (C % 2 == 1);
        } else if (p < 0.75) {
            // R even, C odd
            do { R = rnd.next(lo, hi); } while (R % 2 == 1);
            do { C = rnd.next(lo, hi); } while (C % 2 == 0);
        } else {
            // both even
            do { R = rnd.next(lo, hi); } while (R % 2 == 1);
            do { C = rnd.next(lo, hi); } while (C % 2 == 1);
        }
    }

    // Build grid
    vector<vector<int>> a(R, vector<int>(C));
    if (corridor) {
        // simple random fill
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                a[i][j] = rnd.next(1, ub);
    } else if (R % 2 == 0 && C % 2 == 0) {
        // both even: sometimes enforce unique minimal on odd parity
        if (rnd.next() < 0.5) {
            int mi, mj;
            do {
                mi = rnd.next(0, R - 1);
                mj = rnd.next(0, C - 1);
            } while (((mi + mj) % 2 == 0) || (mi == 0 && mj == 0) || (mi == R - 1 && mj == C - 1));
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if (i == mi && j == mj) a[i][j] = 1;
                    else a[i][j] = rnd.next(2, ub);
                }
            }
        } else {
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++)
                    a[i][j] = rnd.next(1, ub);
        }
    } else {
        // odd-dimension scenarios
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                a[i][j] = rnd.next(1, ub);
    }

    // Output
    println(R, C);
    for (int i = 0; i < R; i++)
        println(a[i]);

    return 0;
}
