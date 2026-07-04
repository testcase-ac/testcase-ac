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

struct TestCase {
    long long S;
    long long a;
    long long A;
    long long b;
    long long B;
};

long long boundedProfit(long long cost) {
    return rnd.next(1LL, min(1000000LL, max(1LL, cost * 2)));
}

TestCase randomCandidate(int mode) {
    if (mode == 0) {
        long long S = rnd.next(1LL, 40LL);
        long long a = rnd.next(1LL, 20LL);
        long long b = rnd.next(1LL, 20LL);
        return {S, a, rnd.next(1LL, 80LL), b, rnd.next(1LL, 80LL)};
    }

    if (mode == 1) {
        long long S = rnd.next(40LL, 5000LL);
        long long a = rnd.next(1LL, 250LL);
        long long b = rnd.next(1LL, 250LL);
        return {S, a, boundedProfit(a), b, boundedProfit(b)};
    }

    if (mode == 2) {
        long long base = rnd.next(1LL, 2000LL);
        long long ma = rnd.next(1LL, 25LL);
        long long mb = rnd.next(1LL, 25LL);
        long long a = base * ma;
        long long b = base * mb;
        long long unit = rnd.next(1LL, 1000LL);
        long long A = min(1000000LL, unit * ma + rnd.next(-3LL, 3LL));
        long long B = min(1000000LL, unit * mb + rnd.next(-3LL, 3LL));
        A = max(1LL, A);
        B = max(1LL, B);
        long long S = rnd.next(max(a, b), min(1000000000LL, base * rnd.next(50LL, 3000LL)));
        return {S, a, A, b, B};
    }

    long long S = rnd.next(1000000LL, 1000000000LL);
    long long a = rnd.next(100000LL, 1000000LL);
    long long b = rnd.next(100000LL, 1000000LL);
    long long A = rnd.next(1LL, min(1000000LL, a));
    long long B = rnd.next(1LL, min(1000000LL, b));
    return {S, a, A, b, B};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    TestCase tc{};
    for (int attempt = 0; attempt < 10000; ++attempt) {
        int mode = rnd.next(0, 3);
        tc = randomCandidate(mode);
        if (maxProfit(tc.S, tc.a, tc.A, tc.b, tc.B) <= 2000000000LL) {
            break;
        }
    }

    println(tc.S);
    println(tc.a, tc.A);
    println(tc.b, tc.B);
    return 0;
}
