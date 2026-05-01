#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (int i = 5; 1LL * i * i <= n; i += 6) {
        if (n % i == 0) return false;
        if (n % (i + 2) == 0) return false;
    }
    return true;
}

int genRandomPalindrome() {
    int L = rnd.next(1, 8); // number of digits
    int half = (L + 1) / 2;
    vector<int> d(L);
    d[0] = rnd.next(1, 9);
    for (int i = 1; i < half; ++i)
        d[i] = rnd.next(0, 9);
    for (int i = 0; i < L - half; ++i)
        d[L - 1 - i] = d[i];
    int x = 0;
    for (int i = 0; i < L; ++i)
        x = x * 10 + d[i];
    return x;
}

int genPalPrime() {
    for (int it = 0; it < 1000; ++it) {
        int x = genRandomPalindrome();
        if (x < 5 || x > 100000000) continue;
        if (x != 2 && x % 2 == 0) continue;
        if (x != 5 && x % 5 == 0) continue;
        if (!isPrime(x)) continue;
        return x;
    }
    static const int fallback[] = {
        5, 7, 11, 101, 131, 151, 181, 191,
        313, 353, 373, 383, 727, 757, 787, 797,
        919, 929, 10301, 10501, 10601, 11311, 11411,
        12421, 12721, 1003001, 1008001, 1022201
    };
    int sz = (int)(sizeof(fallback) / sizeof(fallback[0]));
    return fallback[rnd.next(0, sz - 1)];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a = 5, b = 100000000;
    int scenario = rnd.next(0, 7);

    if (scenario == 0) {
        // Exactly the example range from the statement
        a = 5;
        b = 550;
    } else if (scenario == 1) {
        // Small range including 11 and early palindromic primes
        vector<pair<int,int>> ranges = {
            {5, 20}, {5, 30}, {10, 20}, {10, 40}, {11, 100}, {5, 150}, {5, 200}
        };
        auto p = rnd.any(ranges);
        a = p.first;
        b = p.second;
    } else if (scenario == 2) {
        // Random medium range
        int maxA = 100000000 - 100000;
        a = rnd.next(5, maxA);
        int len = rnd.next(1, 100000);
        b = a + len;
    } else if (scenario == 3) {
        // Near upper limit, relatively narrow
        b = rnd.next(100000000 - 10000, 100000000);
        int len = rnd.next(1, 10000);
        a = b - len;
        if (a < 5) a = 5;
        if (a >= b) a = b - 1;
    } else if (scenario == 4) {
        // Range with no palindromic primes
        vector<pair<int,int>> ranges = {
            {8, 10},
            {20, 30},
            {200, 220},
            {222, 252},
            {4000, 4100}
        };
        auto p = rnd.any(ranges);
        a = p.first;
        b = p.second;
    } else if (scenario == 5) {
        // Wide range starting at 5
        vector<int> ends = {100, 1000, 10000, 100000, 1000000, 100000000};
        b = rnd.any(ends);
        a = 5;
        if (a >= b) b = a + 1;
    } else if (scenario == 6) {
        // Very wide random range
        a = rnd.next(5, 50000000);
        int choice = rnd.next(0, 1);
        if (choice == 0) {
            b = 100000000;
        } else {
            int maxLen = 100000000 - a;
            int len = 1 + rnd.wnext(maxLen, 2); // biased to larger ranges
            long long bb = (long long)a + len;
            if (bb > 100000000LL) bb = 100000000LL;
            b = (int)bb;
        }
        if (a >= b) b = a + 1;
    } else if (scenario == 7) {
        // Range centered around a randomly generated palindromic prime
        int p = genPalPrime();
        int deltaBefore = rnd.next(0, 1000);
        int deltaAfter  = rnd.next(0, 1000);
        long long aa = (long long)p - deltaBefore;
        long long bb = (long long)p + deltaAfter;
        if (aa < 5) aa = 5;
        if (bb > 100000000LL) bb = 100000000LL;
        if (aa == bb) {
            if (bb < 100000000LL) ++bb;
            else --aa;
        }
        a = (int)aa;
        b = (int)bb;
    }

    if (a < 5) a = 5;
    if (b > 100000000) b = 100000000;
    if (a >= b) b = a + 1;
    if (b > 100000000) {
        a -= (b - 100000000);
        b = 100000000;
        if (a < 5) a = 5;
    }

    println(a, b);
    return 0;
}
