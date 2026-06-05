#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll MAX_A = 1000000000000000LL;
    const int MAX_B = 1000000000;

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 4 ? 80 : 30);
    vector<pair<ll, int>> art;
    art.reserve(n);

    if (mode == 0) {
        ll a = rnd.next(1LL, MAX_A);
        for (int i = 0; i < n; ++i) {
            int b = rnd.next(1, 200);
            if (rnd.next(0, 5) == 0) b = rnd.next(1, MAX_B);
            art.push_back({a, b});
        }
    } else if (mode == 1) {
        ll base = rnd.next(1LL, MAX_A - 1000);
        for (int i = 0; i < n; ++i) {
            ll a = base + rnd.next(0, 1000);
            int b = rnd.next(1, 5000);
            art.push_back({a, b});
        }
    } else if (mode == 2) {
        art.push_back({1, rnd.next(1, MAX_B)});
        art.push_back({MAX_A, rnd.next(1, MAX_B)});
        for (int i = 2; i < n; ++i) {
            ll a = rnd.next(1LL, MAX_A);
            int b = rnd.next(1, rnd.next(0, 1) ? 1000 : MAX_B);
            art.push_back({a, b});
        }
    } else if (mode == 3) {
        ll base = rnd.next(1LL, MAX_A - n * 3LL);
        for (int i = 0; i < n; ++i) {
            ll a = base + i * rnd.next(1, 3);
            int b = (i % 3 == 0) ? rnd.next(1, MAX_B) : rnd.next(1, 100);
            art.push_back({a, b});
        }
    } else if (mode == 4) {
        ll blockStart = rnd.next(1LL, MAX_A - 1000000);
        for (int i = 0; i < n; ++i) {
            ll block = rnd.next(0, 3) * 250000LL;
            ll a = blockStart + block + rnd.next(0, 20);
            int b = rnd.next(1, 100000);
            art.push_back({a, b});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            ll a = rnd.next(1LL, MAX_A);
            int b = rnd.next(1, MAX_B);
            art.push_back({a, b});
        }
    }

    if (rnd.next(0, 1)) {
        sort(art.begin(), art.end());
    } else {
        shuffle(art.begin(), art.end());
    }

    println(n);
    for (auto [a, b] : art) {
        println(a, b);
    }

    return 0;
}
