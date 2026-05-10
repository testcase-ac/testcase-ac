#include "testlib.h"
#include <string>

using namespace std;

// Multiply big integer (as digit vector, least significant digit first) by small int
static void mulBigIntByInt(vector<int> &a, long long m) {
    long long carry = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        long long cur = carry + 1LL * a[i] * m;
        a[i] = int(cur % 10);
        carry = cur / 10;
    }
    while (carry > 0) {
        a.push_back(int(carry % 10));
        carry /= 10;
    }
}

// Compute N^P as big integer (in base 10) and return number of digits
static int computePowerDigits(long long N, int P) {
    // Edge cases based on constraints: N>=1, P>=1, so no zero powers.
    vector<int> res(1, 1); // start with 1
    long long base = N;
    int exp = P;

    // binary exponentiation with big-int multiply by small int (base fits long long)
    while (exp > 0) {
        if (exp & 1) {
            // res *= base
            mulBigIntByInt(res, base);
        }
        exp >>= 1;
        if (exp) {
            // base *= base, but this might overflow long long; however, we don't use base for size check.
            // For digit-count correctness we actually must do big-int for base as well.
            // So instead implement plain repeated multiplication: result = N^P directly.
            // We'll break and do that below.
            // To avoid complexity, we instead do straightforward repeated multiplication from start.
            // This function will be replaced by a simple loop.
            break;
        }
    }

    // If we didn't finish via fast exponentiation (i.e., P>1), recompute via repeated multiply.
    if (P > 1) {
        vector<int> a;
        // init a = N
        long long tmp = N;
        if (tmp == 0) return 1; // not used with constraints, but safe
        while (tmp > 0) {
            a.push_back(int(tmp % 10));
            tmp /= 10;
        }
        // compute N^P via repeated multiply
        vector<int> cur = a;
        for (int i = 2; i <= P; ++i) {
            mulBigIntByInt(cur, N);
        }
        return (int)cur.size();
    }

    // P==1
    int cnt = 0;
    long long t = N;
    while (t > 0) {
        ++cnt;
        t /= 10;
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: "N P"
    long long N = inf.readLong(1LL, 2000000000LL, "N");
    inf.readSpace();
    int P = inf.readInt(1, 100000, "P");
    inf.readEoln();

    // Global property from statement: result has at most 15000 digits.
    // We verify this by actually computing the power with big integers.
    // Use straightforward repeated multiplication in computePowerDigits.
    int digits = 0;
    {
        // simple repeated multiplication of big integer by N, P times
        vector<int> a; // least significant digit first
        long long tmp = N;
        while (tmp > 0) {
            a.push_back(int(tmp % 10));
            tmp /= 10;
        }
        for (int i = 2; i <= P; ++i) {
            mulBigIntByInt(a, N);
            // early stop if exceeding limit to avoid unnecessary work
            if ((int)a.size() > 15000) break;
        }
        digits = (int)a.size();
    }

    ensuref(digits <= 15000, "Result N^P has %d digits, exceeds 15000-digit guarantee", digits);

    inf.readEof();
}
