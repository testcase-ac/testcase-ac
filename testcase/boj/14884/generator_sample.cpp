#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

const ll MAX_N = 1000000000000000000LL;

ll smallN() {
    return rnd.next(1LL, 30LL);
}

ll mediumN() {
    return rnd.next(31LL, 1000000LL);
}

ll boundaryN() {
    return MAX_N - rnd.next(0LL, 1000LL);
}

ll residueN(int k) {
    if (k == 0) return smallN();
    ll base = rnd.next(0LL, 1000000LL / k) * k;
    ll offset = rnd.next(0LL, (ll)k - 1);
    return max(1LL, base + offset);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    if (mode == 5) {
        t = 50;
    } else if (mode >= 3) {
        t = rnd.next(8, 20);
    } else {
        t = rnd.next(1, 10);
    }

    vector<pair<ll, int>> cases;
    cases.reserve(t);

    cases.push_back({1, 0});
    if (t >= 2) cases.push_back({1, rnd.next(1, 10)});
    if (t >= 3) cases.push_back({MAX_N, rnd.next(0, 10)});

    while ((int)cases.size() < t) {
        int k;
        ll n;

        if (mode == 0) {
            k = rnd.next(0, 10);
            n = smallN();
        } else if (mode == 1) {
            k = rnd.next(1, 10);
            n = residueN(k);
        } else if (mode == 2) {
            k = 0;
            n = rnd.next(0, 1) == 0 ? smallN() : mediumN();
        } else if (mode == 3) {
            k = rnd.any(vector<int>{1, 2, 3, 9, 10});
            n = rnd.next(0, 2) == 0 ? boundaryN() : residueN(k);
        } else if (mode == 4) {
            k = rnd.next(0, 10);
            n = rnd.next(0, 3) == 0 ? boundaryN() : mediumN();
        } else {
            k = (int)cases.size() % 11;
            int nMode = rnd.next(0, 4);
            if (nMode == 0) n = smallN();
            else if (nMode == 1) n = mediumN();
            else if (nMode == 2) n = boundaryN();
            else n = residueN(k);
        }

        cases.push_back({n, k});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
