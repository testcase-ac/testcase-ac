#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 100000000000000000LL;

    int sizeMode = rnd.next(0, 6);
    int n;
    if (sizeMode == 0) n = 1;
    else if (sizeMode == 1) n = 2;
    else if (sizeMode == 2) n = rnd.next(3, 6);
    else if (sizeMode == 3) n = rnd.next(7, 15);
    else if (sizeMode == 4) n = rnd.next(16, 40);
    else if (sizeMode == 5) n = rnd.next(41, 100);
    else n = rnd.next(101, 220);

    vector<long long> x(n);
    int positionMode = rnd.next(0, 5);
    if (positionMode == 0) {
        long long cur = rnd.next(-30, 30);
        for (int i = 0; i < n; ++i) {
            cur += (i == 0 ? 0 : rnd.next(1, 3));
            x[i] = cur;
        }
    } else if (positionMode == 1) {
        long long cur = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            cur += (i == 0 ? 0 : rnd.next(1, 80));
            x[i] = cur;
        }
    } else if (positionMode == 2) {
        long long cur = rnd.next(-1000000, 1000000);
        for (int i = 0; i < n; ++i) {
            cur += (i == 0 ? 0 : rnd.next(1LL, 1000000LL));
            x[i] = cur;
        }
    } else if (positionMode == 3) {
        long long cur = -LIM + rnd.next(0LL, 1000LL);
        for (int i = 0; i < n; ++i) {
            cur += (i == 0 ? 0 : rnd.next(1LL, 1000000000LL));
            x[i] = cur;
        }
    } else if (positionMode == 4) {
        long long cur = LIM - rnd.next(1000000000000LL, 2000000000000LL);
        for (int i = 0; i < n; ++i) {
            cur += (i == 0 ? 0 : rnd.next(1LL, 1000000000LL));
            x[i] = cur;
        }
    } else {
        long long cur = -rnd.next(1LL, 1000000000000LL);
        for (int i = 0; i < n; ++i) {
            long long gap = (rnd.next(0, 4) == 0 ? rnd.next(1000000000LL, 1000000000000LL) : rnd.next(1LL, 1000LL));
            cur += (i == 0 ? 0 : gap);
            x[i] = cur;
        }
    }

    vector<long long> p(n);
    int powerMode = rnd.next(0, 5);
    for (int i = 0; i < n; ++i) {
        if (powerMode == 0) p[i] = 1;
        else if (powerMode == 1) p[i] = rnd.next(1LL, 8LL);
        else if (powerMode == 2) p[i] = rnd.next(1LL, 1000LL);
        else if (powerMode == 3) p[i] = max(1LL, (i + 1 < n ? x[i + 1] - x[i] : rnd.next(1LL, 1000LL)) - rnd.next(0LL, 3LL));
        else if (powerMode == 4) p[i] = (i + 1 < n ? x[i + 1] - x[i] : rnd.next(1LL, 1000LL)) + rnd.next(0LL, 5LL);
        else p[i] = rnd.next(1000000000000LL, LIM);
    }

    int qMode = rnd.next(0, 4);
    int q;
    if (qMode == 0) q = 1;
    else if (qMode == 1) q = rnd.next(2, 8);
    else if (qMode == 2) q = rnd.next(9, 30);
    else if (qMode == 3) q = rnd.next(31, 80);
    else q = rnd.next(81, 180);

    vector<pair<long long, long long>> queries;
    for (int j = 0; j < q; ++j) {
        long long s;
        int startMode = rnd.next(0, 6);
        if (startMode == 0) {
            s = rnd.any(x);
        } else if (startMode == 1) {
            int idx = rnd.next(0, n - 1);
            s = max(-LIM, x[idx] - rnd.next(1LL, 20LL));
        } else if (startMode == 2) {
            int idx = rnd.next(0, n - 1);
            s = min(LIM, x[idx] + rnd.next(1LL, 20LL));
        } else if (startMode == 3) {
            s = max(-LIM, x.front() - rnd.next(1LL, 1000LL));
        } else if (startMode == 4) {
            s = min(LIM, x.back() + rnd.next(1LL, 1000LL));
        } else if (startMode == 5) {
            s = rnd.next(-1000LL, 1000LL);
        } else {
            s = rnd.next(-LIM, LIM);
        }

        long long t;
        int timeMode = rnd.next(0, 6);
        if (timeMode == 0) t = 1;
        else if (timeMode == 1) t = rnd.next(2LL, 20LL);
        else if (timeMode == 2) t = rnd.next(21LL, 1000LL);
        else if (timeMode == 3) t = rnd.next(1001LL, 1000000LL);
        else if (timeMode == 4) t = rnd.next(1000000000LL, 1000000000000LL);
        else if (timeMode == 5) t = LIM;
        else t = rnd.next(1LL, LIM);

        queries.push_back({s, t});
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(x[i], p[i]);
    }
    println(q);
    for (auto [s, t] : queries) {
        println(s, t);
    }

    return 0;
}
