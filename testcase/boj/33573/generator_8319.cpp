#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool isSquare(ll x) {
    if (x < 0) return false;
    ll k = floor(sqrt((long double)x));
    while (k * k < x) ++k;
    while (k * k > x) --k;
    return k * k == x;
}

ll reverseNum(ll x) {
    string s = to_string(x);
    reverse(s.begin(), s.end());
    int p = 0, n = s.size();
    while (p < n && s[p] == '0') ++p;
    string t = (p == n ? "0" : s.substr(p));
    return stoll(t);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Maximum N = 10^18 - 1 (18 digits)
    ll MAXN = 1;
    for (int i = 0; i < 18; i++) MAXN *= 10;
    MAXN--;

    // Predefined "double-square" numbers (square and reverse-square)
    vector<ll> okNs = {
        1LL, 4LL, 9LL,
        100LL,      // 10^2 -> "001" -> 1
        400LL,      // 20^2 -> "004" -> 4
        121LL,      // 11^2 -> palindrome
        144LL,      // 12^2 -> "441" -> 21^2
        10201LL,    // 101^2 -> palindrome
        12321LL,    // 111^2 -> palindrome
        10000LL,    // 100^2 -> "00001" -> 1
        1000000LL,  // 1000^2 -> "0000001" -> 1
        100000000LL,// 10000^2 -> "000000001" -> 1
        14641LL,    // 121^2 -> palindrome
        40804LL     // 202^2 -> palindrome
    };

    int T = rnd.next(1, 15);
    println(T);
    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 2);
        if (type == 0) {
            // Non-square, varied sizes
            ll N;
            int sub = rnd.next(0, 2);
            ll lo, hi;
            if (sub == 0) {
                lo = 1; hi = 1000;
            } else if (sub == 1) {
                lo = 1001; hi = 1000000;
            } else {
                lo = 1000001; hi = MAXN;
            }
            do {
                N = rnd.next(lo, hi);
            } while (isSquare(N));
            println(N);
        } else if (type == 1) {
            // Square and reverse-square
            println(rnd.any(okNs));
        } else {
            // Square but reverse is not square
            ll N;
            do {
                // pick A small or medium for variety
                ll A;
                if (rnd.next(0,1) == 0) {
                    A = rnd.next(2LL, 1000LL);
                } else {
                    A = rnd.next(1001LL, 1000000LL);
                }
                N = A * A;
            } while (isSquare(reverseNum(N)));
            println(N);
        }
    }

    return 0;
}
