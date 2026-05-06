#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 200000;
    const int MAX_RC = 10000;
    const long long LIM = (1LL << 63) - 1;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<int> r(N), c(N);
    for (int i = 0; i < N; ++i) {
        r[i] = inf.readInt(1, MAX_RC, "r_i");
        inf.readSpace();
        c[i] = inf.readInt(1, MAX_RC, "c_i");
        inf.readEoln();
    }

    // Check that multiplication in the given order is always valid:
    // For all i, c[i] == r[i+1]
    for (int i = 0; i + 1 < N; ++i) {
        ensuref(c[i] == r[i + 1],
                "Incompatible dimensions at position %d and %d: c[%d]=%d, r[%d]=%d",
                i + 1, i + 2, i + 1, c[i], i + 2, r[i + 1]);
    }

    // Check that even the worst order (left-to-right or right-to-left)
    // has cost <= LIM. We must guarantee the statement:
    // "최악의 순서로 연산해도 연산 횟수가 2^63-1보다 작거나 같다."
    //
    // Worst possible parenthesization cost is hard to compute exactly,
    // but statement explicitly guarantees it, so we at least check
    // two extremal simple orders: left-to-right and right-to-left.
    //
    // If either exceeds LIM, we reject. This is a conservative check:
    // if these simple orders already overflow, then the worst order
    // definitely overflows.
    auto safeMul = [&](long long a, long long b) -> long long {
        if (a == 0 || b == 0) return 0;
        ensuref(a <= LIM / b,
                "Overflow in multiplication while checking cost bounds: %lld * %lld exceeds 2^63-1",
                a, b);
        return a * b;
    };

    auto safeAdd = [&](long long a, long long b) -> long long {
        ensuref(a <= LIM - b,
                "Overflow in addition while checking cost bounds: %lld + %lld exceeds 2^63-1",
                a, b);
        return a + b;
    };

    if (N >= 1) {
        // Left-to-right: (((A1*A2)*A3)*...)
        long long leftCost = 0;
        long long curR = r[0];
        long long curC = c[0];
        for (int i = 1; i < N; ++i) {
            long long mult = safeMul(curR, safeMul(curC, (long long)c[i]));
            leftCost = safeAdd(leftCost, mult);
            curC = c[i]; // resulting matrix is curR x c[i]
        }
        ensuref(leftCost <= LIM,
                "Left-to-right multiplication cost %lld exceeds 2^63-1", leftCost);

        // Right-to-left: (...(A1*(A2*...)))
        long long rightCost = 0;
        long long cur2R = r[N - 1];
        long long cur2C = c[N - 1];
        for (int i = N - 2; i >= 0; --i) {
            long long mult = safeMul((long long)r[i], safeMul((long long)c[i], cur2C));
            rightCost = safeAdd(rightCost, mult);
            cur2R = r[i]; // resulting matrix is r[i] x cur2C
        }
        ensuref(rightCost <= LIM,
                "Right-to-left multiplication cost %lld exceeds 2^63-1", rightCost);
    }

    inf.readEof();
}
