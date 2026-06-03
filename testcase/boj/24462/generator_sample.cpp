#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

static pair<ll, ll> makeAlarm(ll d, ll k, int maxShift) {
    ll maxMultiple = d / k;
    ll shift = maxMultiple == 0 ? 0 : rnd.next(0LL, min<ll>(maxMultiple, maxShift));
    return {shift * k, k};
}

static void addRandomAlarm(vector<pair<ll, ll>>& alarms, ll d, ll maxK, int maxShift) {
    ll k = rnd.next(1LL, maxK);
    alarms.push_back(makeAlarm(d, k, maxShift));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    ll d;
    vector<pair<ll, ll>> alarms;

    if (mode == 0) {
        d = rnd.next(1LL, 40LL);
        n = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            addRandomAlarm(alarms, d, min<ll>(d, 12), 4);
        }
    } else if (mode == 1) {
        d = rnd.next(50LL, 250LL);
        n = rnd.next(6, 18);
        ll base = rnd.next(1LL, 8LL);
        for (int i = 0; i < n; ++i) {
            ll k = base * rnd.next(1LL, 12LL);
            alarms.push_back(makeAlarm(d, k, 8));
        }
    } else if (mode == 2) {
        d = rnd.next(100LL, 1000LL);
        n = rnd.next(8, 24);
        for (int i = 0; i < n; ++i) {
            ll k = rnd.next(1LL, 30LL);
            ll maxMultiple = d / k;
            ll shift = maxMultiple == 0 ? 0 : rnd.next(0LL, maxMultiple);
            alarms.push_back({shift * k, k});
        }
    } else if (mode == 3) {
        d = rnd.next(100000000LL, 1000000000LL);
        n = rnd.next(4, 14);
        alarms.push_back({0, 1});
        alarms.push_back({d, 1});
        for (int i = 2; i < n; ++i) {
            ll k = rnd.next(1LL, 1000000000LL);
            alarms.push_back(makeAlarm(d, k, 3));
        }
    } else if (mode == 4) {
        d = rnd.next(1000LL, 100000LL);
        n = rnd.next(10, 35);
        vector<ll> choices = {1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 60};
        for (int i = 0; i < n; ++i) {
            ll k = choices[rnd.next(0, (int)choices.size() - 1)];
            alarms.push_back(makeAlarm(d, k, 20));
        }
    } else {
        d = rnd.next(1LL, 1000000000LL);
        n = rnd.next(2, 10);
        alarms.push_back({0, 1000000000LL});
        alarms.push_back({d, 1});
        for (int i = 2; i < n; ++i) {
            addRandomAlarm(alarms, d, min<ll>(1000000000LL, max(1LL, d * 2)), 5);
        }
    }

    shuffle(alarms.begin(), alarms.end());

    println((int)alarms.size(), d);
    for (auto [t, k] : alarms) {
        println(t, k);
    }

    return 0;
}
