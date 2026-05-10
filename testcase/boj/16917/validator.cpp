#include "testlib.h"

using namespace std;

long long solveCost(long long A, long long B, long long C, long long X, long long Y) {
    long long ans = (1LL << 62);

    // i = number of "half-and-half pairs" (each pair = 2 * C, gives 1 seasoned & 1 fried)
    // We only need to consider up to max(X, Y) pairs.
    for (long long i = 0; i <= max(X, Y); ++i) {
        long long cost = 2LL * C * i;
        long long needA = max(0LL, X - i);
        long long needB = max(0LL, Y - i);
        cost += needA * A + needB * B;
        if (cost < ans) ans = cost;
    }
    return ans;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: five integers on the first line
    long long A = inf.readInt(1, 5000, "A");
    inf.readSpace();
    long long B = inf.readInt(1, 5000, "B");
    inf.readSpace();
    long long C = inf.readInt(1, 5000, "C");
    inf.readSpace();
    long long X = inf.readInt(1, 100000, "X");
    inf.readSpace();
    long long Y = inf.readInt(1, 100000, "Y");
    inf.readEoln();

    // No extra structural/global constraints from the statement
    // However, compute the minimal cost to check overflow bounds, etc.
    long long answer = solveCost(A, B, C, X, Y);

    // The problem's sample 3 suggests that answers can be as large as around 1e8,
    // but there's no explicit upper bound we must enforce.
    // Just ensure the computation did not overflow 64-bit signed range.
    ensuref(answer >= 0 && answer <= (1LL << 60),
            "Computed minimal cost %lld is out of expected safe range", answer);

    inf.readEof();
}
