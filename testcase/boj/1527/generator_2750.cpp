#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;
using ll = long long;

vector<ll> luckies;
void gen(ll x) {
    if (x > 1000000000LL) return;
    luckies.push_back(x);
    gen(x * 10 + 4);
    gen(x * 10 + 7);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate all lucky numbers up to 1e9
    gen(4);
    gen(7);
    sort(luckies.begin(), luckies.end());
    int A, B;
    int t = rnd.next(1, 5);
    if (t == 1) {
        // small random range near start
        A = rnd.next(1, 100);
        B = A + rnd.next(0, 100);
        if (B > 1000000000) B = 1000000000;
    } else if (t == 2) {
        // large suffix range
        A = 1;
        B = rnd.next(100000000, 1000000000);
    } else if (t == 3) {
        // single lucky number
        int idx = rnd.next(0, (int)luckies.size() - 1);
        A = B = (int)luckies[idx];
    } else if (t == 4) {
        // range between two luckies
        int i = rnd.next(0, (int)luckies.size() - 2);
        int j = rnd.next(i + 1, (int)luckies.size() - 1);
        A = (int)luckies[i];
        B = (int)luckies[j];
    } else {
        // gap with no luckies
        int i = rnd.next(0, (int)luckies.size() - 2);
        ll lo = luckies[i] + 1;
        ll hi = luckies[i + 1] - 1;
        if (lo <= hi) {
            A = (int)lo;
            B = (int)hi;
        } else {
            // fallback small random
            A = rnd.next(1, 1000);
            B = A + rnd.next(0, 1000);
            if (B > 1000000000) B = 1000000000;
        }
    }
    if (A < 1) A = 1;
    if (B < A) B = A;
    println(A, B);
    return 0;
}
