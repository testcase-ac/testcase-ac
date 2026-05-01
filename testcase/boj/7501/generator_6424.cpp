#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using u128 = unsigned __int128;
using u64 = unsigned long long;

// Miller-Rabin for 64-bit
u64 mod_mul(u64 a, u64 b, u64 m) {
    u128 r = (u128)a * b;
    return (u64)(r % m);
}
u64 mod_pow(u64 a, u64 d, u64 m) {
    u64 r = 1;
    while (d) {
        if (d & 1) r = mod_mul(r, a, m);
        a = mod_mul(a, a, m);
        d >>= 1;
    }
    return r;
}
bool isPrime64(u64 n) {
    if (n < 2) return false;
    for (u64 p: {2ull,3ull,5ull,7ull,11ull,13ull,17ull,19ull,23ull,29ull,31ull,37ull})
        if (n%p==0) return n==p;
    u64 d = n-1, s = 0;
    while ((d&1)==0) { d>>=1; s++; }
    for (u64 a: {2ull, 325ull, 9375ull, 28178ull, 450775ull, 9780504ull, 1795265022ull}) {
        if (a%n==0) continue;
        u64 x = mod_pow(a, d, n);
        if (x==1 || x==n-1) continue;
        bool comp = true;
        for (u64 r = 1; r < s; ++r) {
            x = mod_mul(x, x, n);
            if (x == n-1) {
                comp = false;
                break;
            }
        }
        if (comp) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter: window max width W (0..100)
    vector<int> Ws = {1,2,5,10,20,50,100};
    int W = rnd.any(Ws);
    // Hyperparameter: pick region for prime K
    int region = rnd.next(0, 2);
    u64 K = 0;
    if (region == 0) {
        // small region [3, 1000]
        vector<u64> cand;
        for (u64 i = 3; i <= 1000; i += 2)
            if (isPrime64(i)) cand.push_back(i);
        shuffle(cand.begin(), cand.end());
        K = cand[rnd.next((int)cand.size())];
    } else if (region == 1) {
        // medium [1e6, 1e9]
        while (true) {
            u64 x = rnd.next((u64)1000000, (u64)1000000000);
            if ((x & 1) == 0) x++;
            if (isPrime64(x)) { K = x; break; }
        }
    } else {
        // large [1e17, 1e18]
        while (true) {
            u64 x = rnd.next((u64)100000000000000000, (u64)1000000000000000000ULL);
            if ((x & 1) == 0) x++;
            if (isPrime64(x)) { K = x; break; }
        }
    }
    // pick window around K: choose L and R such that R+L <= W
    int maxL = min<u64>(W, K > 3 ? K - 3 : 0);
    int L = rnd.next(0, maxL);
    int R = rnd.next(0, W - L);
    u64 A = K - L;
    if (A < 3) A = 3;
    u64 B = K + R;
    // ensure A < B
    if (A >= B) {
        if (A + 1 <= (u64)1e18) B = A + 1;
        else A = B - 1;
    }
    println(A, B);
    return 0;
}
