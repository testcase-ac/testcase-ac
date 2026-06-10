#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 8);

    vector<ll> a(n);
    vector<pair<ll, ll>> conditions;

    if (mode == 3) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 5);
        a.assign(n, 1);
        for (ll& x : a) {
            x = rnd.next(0, 1) ? rnd.next(999999900, 1000000000) : rnd.next(1, 100);
        }

        ll t = rnd.next(999999900, 1000000000);
        ll q = rnd.next(1, 1000);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 2) != 0) {
                t = min(1000000000LL, t + rnd.next(0, 10));
            }
            q = min(1000000000LL, q + rnd.next(0, 300000000));
            conditions.emplace_back(t, q);
        }
    } else {
        for (ll& x : a) {
            int valueMode = rnd.next(0, 2);
            if (valueMode == 0) {
                x = rnd.next(1, 20);
            } else if (valueMode == 1) {
                x = rnd.next(1, 1000);
            } else {
                x = rnd.next(900000000, 1000000000);
            }
        }

        vector<ll> t(m);
        ll curT = rnd.next(1, 4);
        for (int i = 0; i < m; ++i) {
            if (i > 0) {
                int step = (mode == 1 && rnd.next(0, 1) == 0) ? 0 : rnd.next(0, 5);
                curT = min(1000000000LL, curT + step);
            }
            t[i] = curT;
        }

        vector<ll> sortedA = a;
        sort(sortedA.rbegin(), sortedA.rend());
        ll feasible = 0;
        int used = 0;
        ll q = 0;

        for (int i = 0; i < m; ++i) {
            if (mode == 2 && i == 0) {
                q = min(1000000000LL, sortedA[0] + t[i] + rnd.next(1, 30));
            } else {
                int take = rnd.next(0, max(0, n - used));
                for (int j = 0; j < take; ++j) {
                    feasible += sortedA[used++] + t[i];
                }

                ll bump;
                if (mode == 0) {
                    bump = rnd.next(0, 30);
                } else if (mode == 1) {
                    bump = rnd.next(0, 1) ? 0 : rnd.next(1, 20);
                } else {
                    bump = rnd.next(0, 100);
                }
                q = min(1000000000LL, max(q, max(1LL, feasible + bump)));
            }
            conditions.emplace_back(t[i], q);
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    for (auto [t, q] : conditions) {
        println(t, q);
    }

    return 0;
}
