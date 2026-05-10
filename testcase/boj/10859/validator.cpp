#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// 64-bit Miller-Rabin for n <= 1e16 (actually works up to 2^64)
long long mulmod(long long a, long long b, long long mod) {
    __int128 x = ( __int128)a * b;
    x %= mod;
    return (long long)x;
}

long long powmod(long long a, long long e, long long mod) {
    long long r = 1 % mod;
    long long x = a % mod;
    while (e > 0) {
        if (e & 1) r = mulmod(r, x, mod);
        x = mulmod(x, x, mod);
        e >>= 1;
    }
    return r;
}

bool isPrimeDet(long long n) {
    if (n < 2) return false;
    for (long long p : {2,3,5,7,11,13}) {
        if (n == p) return true;
        if (n % p == 0) return (n == p);
    }
    long long d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    auto check = [&](long long a) -> bool {
        if (a % n == 0) return true;
        long long x = powmod(a, d, n);
        if (x == 1 || x == n - 1) return true;
        for (int r = 1; r < s; ++r) {
            x = mulmod(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };

    // Deterministic bases for 64-bit
    for (long long a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (!check(a)) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read entire line as token to preserve canonical form check ourselves.
    string s = inf.readToken("[0-9]+", "N");
    inf.readEoln();
    inf.readEof();

    // Check length constraint via value bound: 1 <= N <= 1e16
    // First, no leading zero
    ensuref(s.size() == 1 || s[0] != '0', "N has leading zeros or is empty");

    // Compare as string to 10^16 = "10000000000000000"
    const string MAXN = "10000000000000000";
    // Ensure N >= 1
    ensuref(!(s.size() == 1 && s[0] == '0'), "N must be at least 1");

    if (s.size() > MAXN.size())
        ensuref(false, "N is larger than 1e16");
    if (s.size() == MAXN.size() && s > MAXN)
        ensuref(false, "N is larger than 1e16");

    // Convert to long long (safe since N <= 1e16 < 2^63)
    long long n = 0;
    for (char c : s) {
        n = n * 10 + (c - '0');
    }

    // Build 180-degree rotated number as string, validating that
    // all digits are rotatable and mapping is correct.
    // Mapping: 0->0, 1->1, 2,5,6,8,9 defined as in statement
    // from description (Korean):
    // - 0,1,8 stay same
    // - 6 <-> 9
    // - 2 <-> 5
    // - 3,4,7 are invalid
    auto mapDigit = [](char d) -> char {
        switch (d) {
            case '0': return '0';
            case '1': return '1';
            case '8': return '8';
            case '2': return '5';
            case '5': return '2';
            case '6': return '9';
            case '9': return '6';
            default: return '?'; // invalid
        }
    };

    string rotated;
    rotated.reserve(s.size());
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        char md = mapDigit(s[i]);
        if (md == '?') {
            // When rotated, it's no longer a number; according to statement,
            // in that case the rotated one is just "not prime".
            rotated.clear();
            break;
        }
        rotated.push_back(md);
    }

    // Also enforce no leading zero on rotated, if it exists
    if (!rotated.empty()) {
        ensuref(rotated.size() == 1 || rotated[0] != '0',
                "Rotated representation has leading zero, which should not occur for a valid digital display number");
    }

    long long nr = -1;
    if (!rotated.empty()) {
        // rotated length is at most original, and original <= 1e16, so safe
        __int128 tmp = 0;
        for (char c : rotated) {
            tmp = tmp * 10 + (c - '0');
        }
        ensuref(tmp <= ( __int128)LLONG_MAX, "Rotated value exceeds 64-bit range");
        nr = (long long)tmp;
    }

    // According to the statement, test data guarantees:
    // - If N is prime, then "answer exists" about being able to test rotated prime.
    // That simply means nothing special; but we can still check the implied condition:
    bool primeN = isPrimeDet(n);
    bool primeR = false;
    if (!rotated.empty()) {
        primeR = isPrimeDet(nr);
    } else {
        // If rotated not a valid number, then it's certainly not prime
        primeR = false;
    }

    // No further global constraints promised by statement (like "answer at most X").
    // We computed primes only to potentially check such guarantees; none here to enforce.

    return 0;
}
