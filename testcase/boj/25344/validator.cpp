#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long safe_gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long safe_lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    long long g = safe_gcd(a, b);
    // check overflow of a/g * b > 1e9
    long long x = a / g;
    // We only need to ensure result <= 1e9 as per statement
    // Use __int128 to avoid intermediate overflow
    __int128 mul = (__int128)x * (__int128)b;
    ensuref(mul <= 1000000000LL, "LCM exceeds 1e9 during computation");
    return (long long)mul;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 100000, "N");
    inf.readEoln();

    int cnt = N - 2;
    vector<int> T;
    if (cnt > 0) {
        T = inf.readInts(cnt, 1, 100000, "T_i");
    }
    inf.readEoln();

    // Holistic check: there exists a global period <= 1e9.
    // The global period is LCM of all T_i (because each triple aligns every T_i seconds).
    // Problem guarantees it exists and <= 1e9, so verify.
    long long period = 1;
    for (int i = 0; i < cnt; ++i) {
        period = safe_lcm(period, (long long)T[i]);
        ensuref(period <= 1000000000LL,
                "Global period exceeds 1e9 after including T_%d = %d", i + 1, T[i]);
    }
    ensuref(period >= 1 && period <= 1000000000LL,
            "Global period must be in [1, 1e9], got %lld", period);

    inf.readEof();
}
