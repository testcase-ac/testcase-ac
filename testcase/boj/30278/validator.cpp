#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long profitFor(long long s, long long a, long long A, long long b, long long B,
                    long long countA) {
    return A * countA + B * ((s - a * countA) / b);
}

long long maxProfit(long long s, long long a, long long A, long long b, long long B) {
    vector<long long> countsA;
    long long maxA = s / a;
    long long period = b / gcd(a, b);
    long long prefix = min(maxA, period - 1);

    for (long long x = 0; x <= prefix; ++x) {
        countsA.push_back(x);
    }
    for (long long x = max(0LL, maxA - period + 1); x <= maxA; ++x) {
        countsA.push_back(x);
    }

    long long best = 0;
    for (long long x : countsA) {
        best = max(best, profitFor(s, a, A, b, B, x));
    }
    return best;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long S = inf.readLong(1LL, 1000000000LL, "S");
    inf.readEoln();

    long long a = inf.readLong(1LL, 1000000LL, "a");
    inf.readSpace();
    long long A = inf.readLong(1LL, 1000000LL, "A");
    inf.readEoln();

    long long b = inf.readLong(1LL, 1000000LL, "b");
    inf.readSpace();
    long long B = inf.readLong(1LL, 1000000LL, "B");
    inf.readEoln();

    ensuref(maxProfit(S, a, A, b, B) <= 2000000000LL,
            "maximum profit exceeds the stated bound");

    inf.readEof();
}
