#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;

const int64 MAX_D = 100000000000LL;
const int64 MAX_P = 266000000000LL;
const int MAX_Q = 1596506;

int64 clampHealth(int64 value) {
    return max(1LL, min(MAX_P, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int k;
    vector<int64> damage;
    vector<pair<int64, int>> bosses;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, n);
        k = rnd.next(1, 5);

        for (int i = 0; i < n; ++i) {
            damage.push_back(rnd.next(1LL, 30LL));
        }
        for (int i = 0; i < k; ++i) {
            int64 base = rnd.any(damage);
            int seconds = rnd.next(1, 1200);
            int64 p = clampHealth(base * seconds + rnd.next(0LL, base - 1));
            int q = rnd.next(1, 500);
            bosses.emplace_back(p, q);
        }
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        m = rnd.next(1, n);
        k = rnd.next(6, 13);

        for (int i = 0; i < n; ++i) {
            damage.push_back(rnd.next(1LL, 2000000000LL));
        }
        for (int i = 0; i < k; ++i) {
            int64 base = rnd.any(damage);
            int seconds = rnd.any(vector<int>{1, 2, 899, 900, 901, 1200});
            int64 p = clampHealth(base * seconds + rnd.next(0LL, min(base - 1, 1000000LL)));
            int q = rnd.next(1, MAX_Q);
            bosses.emplace_back(p, q);
        }
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        m = rnd.next(max(1, n / 2), n);
        k = 13;

        for (int i = 0; i < n; ++i) {
            damage.push_back(rnd.next(1LL, MAX_D));
        }
        for (int i = 0; i < k; ++i) {
            int64 p = rnd.next(1LL, MAX_P);
            int q = rnd.next(1, MAX_Q);
            bosses.emplace_back(p, q);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        m = rnd.next(1, n);
        k = rnd.next(2, 8);

        int64 commonDamage = rnd.next(1LL, 1000000LL);
        for (int i = 0; i < n; ++i) {
            damage.push_back(commonDamage + rnd.next(0LL, 3LL));
        }
        for (int i = 0; i < k; ++i) {
            int seconds = rnd.next(850, 950);
            int64 p = clampHealth(commonDamage * seconds + rnd.next(0LL, commonDamage - 1));
            int q = rnd.next(1, 10000);
            bosses.emplace_back(p, q);
        }
    } else if (mode == 4) {
        n = rnd.next(13, 25);
        m = rnd.next(1, 5);
        k = rnd.next(8, 13);

        for (int i = 0; i < n; ++i) {
            damage.push_back(rnd.next(1LL, 500000000LL));
        }
        sort(damage.begin(), damage.end());
        for (int i = 0; i < k; ++i) {
            int64 base = damage[rnd.next(max(0, n - 5), n - 1)];
            int seconds = rnd.next(100, 1100);
            int64 p = clampHealth(base * seconds);
            int q = rnd.next(1, MAX_Q);
            bosses.emplace_back(p, q);
        }
    } else {
        n = 49;
        m = rnd.next(1, n);
        k = 13;

        for (int i = 0; i < n; ++i) {
            damage.push_back(rnd.next(1LL, MAX_D));
        }
        damage[rnd.next(0, n - 1)] = MAX_D;
        for (int i = 0; i < k; ++i) {
            int64 p = (rnd.next(0, 3) == 0) ? MAX_P : rnd.next(1LL, MAX_P);
            int q = (rnd.next(0, 3) == 0) ? MAX_Q : rnd.next(1, MAX_Q);
            bosses.emplace_back(p, q);
        }
    }

    shuffle(damage.begin(), damage.end());
    shuffle(bosses.begin(), bosses.end());

    println(n, m, k);
    for (int64 d : damage) {
        println(d);
    }
    for (auto [p, q] : bosses) {
        println(p, q);
    }

    return 0;
}
