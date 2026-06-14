#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

const ll MIN_A = -1000000000LL;
const ll MAX_A = 1000000000LL;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 18);
    ll k = rnd.next(1LL, 60LL);
    vector<ll> a(n);

    if (mode == 0) {
        k = rnd.next(1LL, 12LL);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1LL, k);
        }
    } else if (mode == 1) {
        k = rnd.next(1LL, 40LL);
        ll low = rnd.next(1LL, min(k, 8LL));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(low, k);
        }
        a[rnd.next(n)] = low;
    } else if (mode == 2) {
        k = rnd.next(1LL, 50LL);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1LL, k);
        }
        a[rnd.next(n)] = rnd.next(k + 1, k + 30);
    } else if (mode == 3) {
        k = rnd.next(1LL, 50LL);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1LL, k);
        }
        int pos = rnd.next(n);
        a[pos] = rnd.next(0, 1) == 0 ? 0 : -rnd.next(1LL, 30LL);
    } else if (mode == 4) {
        k = rnd.next(1LL, 100LL);
        ll value = rnd.next(1LL, k);
        fill(a.begin(), a.end(), value);
        if (rnd.next(0, 2) == 0) {
            a[rnd.next(n)] = rnd.next(0, 1) == 0 ? 0 : -value;
        }
    } else if (mode == 5) {
        n = rnd.next(2, 10);
        a.assign(n, 0);
        k = rnd.next(999999900LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 5);
            if (pick == 0) {
                a[i] = MIN_A;
            } else if (pick == 1) {
                a[i] = MAX_A;
            } else if (pick == 2) {
                a[i] = 0;
            } else if (pick == 3) {
                a[i] = k;
            } else {
                a[i] = rnd.next(-100LL, 100LL);
            }
        }
    } else {
        n = rnd.next(2, 60);
        a.assign(n, 0);
        k = rnd.next(1LL, 1000000000LL);
        ll lo = rnd.next(-1000LL, 1000LL);
        ll hi = rnd.next(lo, min(MAX_A, lo + rnd.next(0LL, 5000LL)));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    }

    shuffle(a.begin(), a.end());

    println(n, k);
    println(a);
    return 0;
}
