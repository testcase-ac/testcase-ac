#include "testlib.h"
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read R, L
    ll R = inf.readLong(1LL, 1000000000LL, "R");
    inf.readSpace();
    ll L = inf.readLong(1LL, 1000000000LL, "L");
    inf.readEoln();

    // 2. Read N, M
    int N = inf.readInt(0, 100, "N");
    inf.readSpace();
    int M = inf.readInt(0, 100, "M");
    inf.readEoln();

    // 3. Read N lotus leaves
    vector<ll> x_lotus(N), y_lotus(N), r_lotus(N);
    for (int i = 0; i < N; ++i) {
        x_lotus[i] = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        y_lotus[i] = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readSpace();
        r_lotus[i] = inf.readLong(1LL, 1000000000LL, "r_i");
        inf.readEoln();

        // Check that the center is inside or on the pond
        ll dist2 = x_lotus[i] * x_lotus[i] + y_lotus[i] * y_lotus[i];
        ensuref(dist2 <= R * R, 
            "Lotus leaf %d center (%.0f, %.0f) is outside the pond of radius %lld", 
            i+1, (double)x_lotus[i], (double)y_lotus[i], R);

        // Check that the entire lotus leaf is inside or on the pond
        // (Not required by statement: only center must be inside or on pond)
        // So, do not check for (distance + r_i <= R)
    }

    // 4. Read M ducks
    vector<ll> x_duck(M), y_duck(M);
    for (int i = 0; i < M; ++i) {
        x_duck[i] = inf.readLong(-1000000000LL, 1000000000LL, "x_j");
        inf.readSpace();
        y_duck[i] = inf.readLong(-1000000000LL, 1000000000LL, "y_j");
        inf.readEoln();

        // Check that the duck is inside or on the pond
        ll dist2 = x_duck[i] * x_duck[i] + y_duck[i] * y_duck[i];
        ensuref(dist2 <= R * R, 
            "Duck %d at (%.0f, %.0f) is outside the pond of radius %lld", 
            i+1, (double)x_duck[i], (double)y_duck[i], R);
    }

    inf.readEof();
}
