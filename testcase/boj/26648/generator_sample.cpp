#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

const ll MAX_SCORE = 2000000000LL;

vector<ll> makeTriple(ll low, ll high) {
    vector<ll> v(3);
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        v = {low, high, rnd.next(low, high)};
    } else if (mode == 1) {
        v = {low, low, high};
    } else if (mode == 2) {
        v = {low, high, high};
    } else if (mode == 3) {
        v = {rnd.next(low, high), rnd.next(low, high), rnd.next(low, high)};
    } else if (mode == 4) {
        ll mid = low + (high - low) / 2;
        v = {low, mid, high};
    } else {
        v = {high, low, rnd.next(low, high)};
    }

    shuffle(v.begin(), v.end());
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 18);
    if (mode == 7) {
        n = rnd.next(30, 80);
    }

    vector<ll> a(n), b(n), c(n);
    ll current = rnd.next(0LL, 20LL);

    for (int i = 0; i < n; ++i) {
        ll low = 0;
        ll high = 0;

        if (mode == 0) {
            low = current;
            high = current + rnd.next(0LL, 5LL);
            current = high + rnd.next(1LL, 4LL);
        } else if (mode == 1) {
            low = rnd.next(0LL, 12LL);
            high = low + rnd.next(0LL, 4LL);
        } else if (mode == 2) {
            high = rnd.next(0LL, 8LL);
            low = rnd.next(0LL, high);
        } else if (mode == 3) {
            low = rnd.next(0LL, 3LL);
            high = rnd.next(MAX_SCORE - 20LL, MAX_SCORE);
        } else if (mode == 4) {
            ll center = rnd.next(0LL, 25LL);
            low = center;
            high = center;
        } else if (mode == 5) {
            low = rnd.next(0LL, 40LL);
            high = min(MAX_SCORE, low + rnd.next(0LL, 30LL));
            if (i > 0 && rnd.next(0, 2) == 0) {
                high = rnd.next(0LL, min<ll>(high, a[i - 1] + b[i - 1] + c[i - 1]));
                low = rnd.next(0LL, high);
            }
        } else if (mode == 6) {
            low = rnd.next(0LL, 100LL);
            high = rnd.next(low, min(MAX_SCORE, low + 100LL));
            if (rnd.next(0, 5) == 0) {
                low = MAX_SCORE - rnd.next(0LL, 5LL);
                high = MAX_SCORE;
            }
        } else {
            low = rnd.next(0LL, 1000000LL);
            high = rnd.next(low, min(MAX_SCORE, low + 1000000LL));
        }

        vector<ll> triple = makeTriple(low, high);
        a[i] = triple[0];
        b[i] = triple[1];
        c[i] = triple[2];
    }

    println(n);
    println(a);
    println(b);
    println(c);

    return 0;
}
