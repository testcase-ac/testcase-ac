#include "testlib.h"
using namespace std;

using ull = unsigned long long;
const ull MAXN = 10000000000000000ull; // 1e16

ull strToULL(const string &s) {
    ull x = 0;
    for (char c : s) {
        x = x * 10 + (c - '0');
    }
    return x;
}

string rotateStrFromString(const string &s) {
    string t;
    t.reserve(s.size());
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        char c = s[i];
        char m;
        if (c == '0' || c == '1' || c == '2' || c == '5' || c == '8') {
            m = c;
        } else if (c == '6') {
            m = '9';
        } else if (c == '9') {
            m = '6';
        } else {
            return "";
        }
        t.push_back(m);
    }
    return t;
}

string rotateStrFromULL(ull n) {
    return rotateStrFromString(to_string(n));
}

bool containsInvalidDigits(ull n) {
    string s = to_string(n);
    for (char c : s) {
        if (c == '3' || c == '4' || c == '7') return true;
    }
    return false;
}

// Miller-Rabin for 64-bit
ull mulmod(ull a, ull b, ull mod) {
    __uint128_t res = ( __uint128_t)a * b;
    res %= mod;
    return (ull)res;
}

ull powmod(ull a, ull d, ull mod) {
    ull r = 1;
    while (d) {
        if (d & 1) r = mulmod(r, a, mod);
        a = mulmod(a, a, mod);
        d >>= 1;
    }
    return r;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    static ull smallPrimes[] = {2ull,3ull,5ull,7ull,11ull,13ull,17ull,19ull,23ull,29ull,31ull,37ull};
    for (ull p : smallPrimes) {
        if (n == p) return true;
        if (n % p == 0ull) return n == p;
    }
    ull d = n - 1;
    int s = 0;
    while ((d & 1ull) == 0ull) {
        d >>= 1;
        ++s;
    }
    auto check = [&](ull a) {
        if (a % n == 0ull) return true;
        ull x = powmod(a, d, n);
        if (x == 1ull || x == n - 1) return true;
        for (int i = 1; i < s; ++i) {
            x = mulmod(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };
    ull bases[] = {2ull, 325ull, 9375ull, 28178ull, 450775ull, 9780504ull, 1795265022ull};
    for (ull a : bases) {
        if (a % n == 0ull) continue;
        if (!check(a)) return false;
    }
    return true;
}

// Scenario helpers

ull generateYesCase() {
    // N prime, rotated N' prime, rotation valid, no leading zero
    for (int it = 0; it < 50000; ++it) {
        ull n = (ull)rnd.next(2LL, 10000000LL); // keep reasonably small
        if (n % 10 == 0) continue; // avoid leading zero after rotation
        string rot = rotateStrFromULL(n);
        if (rot.empty()) continue;
        if (rot[0] == '0') continue; // safety
        ull rn = strToULL(rot);
        if (isPrime(n) && isPrime(rn)) return n;
    }
    // Fallback known good examples
    vector<ull> fallback = {2ull, 5ull, 11ull, 101ull, 151ull, 181ull};
    return rnd.any(fallback);
}

ull generatePrimeWithCompositeRotation() {
    for (int it = 0; it < 500000; ++it) {
        ull n = (ull)rnd.next(2LL, 1000000000LL);
        if (n % 10 == 0) continue;
        string rot = rotateStrFromULL(n);
        if (rot.empty()) continue;
        if (rot[0] == '0') continue;
        ull rn = strToULL(rot);
        if (isPrime(n) && !isPrime(rn)) return n;
    }
    // Fallback example from statement
    return 18115211ull;
}

ull generatePrimeWithInvalidDigit() {
    for (int it = 0; it < 200000; ++it) {
        ull n = (ull)rnd.next(2LL, (long long)MAXN);
        if (n % 10 == 0) continue; // avoid rotated leading zero just in case
        if (!containsInvalidDigits(n)) continue;
        if (isPrime(n)) return n;
    }
    return 13ull; // prime containing '3'
}

ull generateCompositeValidDigitsPrimeRotation() {
    for (int it = 0; it < 500000; ++it) {
        ull n = (ull)rnd.next(2LL, 10000000LL);
        if (n % 10 == 0) continue;
        if (containsInvalidDigits(n)) continue;
        string rot = rotateStrFromULL(n);
        if (rot.empty()) continue;
        if (rot[0] == '0') continue;
        ull rn = strToULL(rot);
        if (!isPrime(n) && isPrime(rn)) return n;
    }
    return 62ull; // 62 composite, rotated 29 prime
}

ull generateCompositeValidDigitsCompositeRotation() {
    for (int it = 0; it < 200000; ++it) {
        ull n = (ull)rnd.next(2LL, 10000000LL);
        if (n % 10 == 0) continue;
        if (containsInvalidDigits(n)) continue;
        string rot = rotateStrFromULL(n);
        if (rot.empty()) continue;
        if (rot[0] == '0') continue;
        ull rn = strToULL(rot);
        if (!isPrime(n) && !isPrime(rn)) return n;
    }
    return 12ull; // 12 composite, rotated 21 composite
}

ull generateCompositeWithInvalidDigit() {
    for (int it = 0; it < 200000; ++it) {
        ull n = (ull)rnd.next(4LL, (long long)MAXN);
        if (n % 10 == 0) continue;
        if (!containsInvalidDigits(n)) continue;
        if (!isPrime(n)) return n;
    }
    return 14ull; // composite, contains '4'
}

ull generateBigPrime() {
    ull lo = MAXN / 100; // around 1e14
    for (int it = 0; it < 200000; ++it) {
        ull n = (ull)rnd.next((long long)lo, (long long)MAXN);
        if (n % 10 == 0) continue; // avoid potential rotated leading zero
        if (isPrime(n)) return n;
    }
    // Fallback to known prime
    return 1000000007ull;
}

ull generateBigComposite() {
    ull lo = MAXN / 100;
    while (true) {
        ull n = (ull)rnd.next((long long)lo, (long long)MAXN);
        if (n % 2 == 1) continue;   // ensure composite (even and >2)
        if (n <= 2) continue;
        if (n % 10 == 0) continue;   // avoid rotated leading zero
        return n;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(1, 9);
    ull N;

    switch (type) {
        case 1:
            // Yes-case: prime and rotated prime
            N = generateYesCase();
            break;
        case 2:
            // Prime, rotation composite (often example)
            if (rnd.next(0, 1) == 0) N = 18115211ull;
            else N = generatePrimeWithCompositeRotation();
            break;
        case 3:
            // Prime containing invalid digits (3,4,7)
            N = generatePrimeWithInvalidDigit();
            break;
        case 4:
            // Composite, valid digits, rotation prime
            if (rnd.next(0, 3) == 0) N = 62ull;
            else N = generateCompositeValidDigitsPrimeRotation();
            break;
        case 5:
            // Composite, valid digits, rotation composite
            N = generateCompositeValidDigitsCompositeRotation();
            break;
        case 6:
            // Composite with invalid digit(s)
            N = generateCompositeWithInvalidDigit();
            break;
        case 7:
            // Large prime near limit
            N = generateBigPrime();
            break;
        case 8:
            // Large composite near limit
            N = generateBigComposite();
            break;
        case 9:
        default:
            // Random number in range, avoiding last digit 0
            do {
                N = (ull)rnd.next(1LL, (long long)MAXN);
            } while (N % 10 == 0);
            break;
    }

    println(to_string(N));
    return 0;
}
