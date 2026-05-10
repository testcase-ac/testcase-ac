#include "testlib.h"
#include <vector>
using namespace std;

int N;
vector<vector<int>> a;

long long solveRec(int r1, int r2, int c1, int c2, int lastDir) {
    // lastDir: 0 = none, 1 = horizontal, 2 = vertical
    int imp = 0, gem = 0;
    for (int i = r1; i < r2; ++i)
        for (int j = c1; j < c2; ++j) {
            if (a[i][j] == 1) ++imp;
            else if (a[i][j] == 2) ++gem;
        }
    if (gem == 0) return 0;
    if (imp == 0) return (gem == 1 ? 1 : 0);

    long long ways = 0;

    // horizontal cuts: cut line is row k, between rows [r1,k) and [k+1,r2)
    if (lastDir != 1) {
        for (int k = r1; k < r2; ++k) {
            bool hasImp = false;
            bool hasGemOnLine = false;
            for (int j = c1; j < c2; ++j) {
                if (a[k][j] == 1) hasImp = true;
                if (a[k][j] == 2) hasGemOnLine = true;
            }
            if (hasImp && !hasGemOnLine) {
                long long left = solveRec(r1, k, c1, c2, 1);
                long long right = solveRec(k + 1, r2, c1, c2, 1);
                ways += left * right;
            }
        }
    }

    // vertical cuts: cut line is column k, between [c1,k) and [k+1,c2)
    if (lastDir != 2) {
        for (int k = c1; k < c2; ++k) {
            bool hasImp = false;
            bool hasGemOnLine = false;
            for (int i = r1; i < r2; ++i) {
                if (a[i][k] == 1) hasImp = true;
                if (a[i][k] == 2) hasGemOnLine = true;
            }
            if (hasImp && !hasGemOnLine) {
                long long left = solveRec(r1, r2, c1, k, 2);
                long long right = solveRec(r1, r2, k + 1, c2, 2);
                ways += left * right;
            }
        }
    }

    return ways;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    N = inf.readInt(1, 20, "N");
    inf.readEoln();

    a.assign(N, vector<int>(N));
    int totalGems = 0;

    for (int i = 0; i < N; ++i) {
        a[i][0] = inf.readInt(0, 2, "cell");
        for (int j = 1; j < N; ++j) {
            inf.readSpace();
            a[i][j] = inf.readInt(0, 2, "cell");
        }
        inf.readEoln();
        for (int j = 0; j < N; ++j)
            if (a[i][j] == 2) ++totalGems;
    }

    ensuref(totalGems <= 15, "Number of gems must be at most 15, got %d", totalGems);

    // Global property: answer always exists is NOT stated,
    // but we must ensure output fits in 32-bit signed as typical BOJ spec.
    // Compute number of ways and ensure it is within reasonable range.
    long long ways = solveRec(0, N, 0, N, 0);
    // Problem output is a single integer or -1; ensure we can represent it safely.
    ensuref(ways >= 0 && ways <= 1000000000LL,
            "Number of valid cutting ways out of expected bounds: %lld", ways);

    inf.readEof();
}
