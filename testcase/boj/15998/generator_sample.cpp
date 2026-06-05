#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

constexpr ll LIMIT = 1000000000000000000LL;

struct Entry {
    ll a;
    ll b;
};

ll randAmount(ll hi = 1000000) {
    return rnd.next(1LL, hi);
}

void addDeposit(vector<Entry>& log, ll& balance, ll amount) {
    balance = min(LIMIT, balance + amount);
    log.push_back({amount, balance});
}

void addWithdrawal(vector<Entry>& log, ll& balance, ll amount, ll unit) {
    ll before = balance;
    while (balance < amount) balance += unit;
    balance -= amount;
    if (balance > LIMIT) balance = rnd.next(0LL, min(unit - 1, LIMIT));
    log.push_back({-amount, balance});
    (void)before;
}

void makeConsistent(vector<Entry>& log) {
    ll balance = 0;
    ll unit = rnd.next(2LL, 100000LL);
    int n = rnd.next(1, 20);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 3);
        if (mode == 0 || balance == 0) {
            addDeposit(log, balance, randAmount(200000));
        } else if (mode == 1) {
            ll amount = rnd.next(1LL, max(1LL, balance + unit * 2));
            addWithdrawal(log, balance, amount, unit);
        } else if (mode == 2) {
            ll amount = balance + rnd.next(1LL, unit * 3);
            addWithdrawal(log, balance, amount, unit);
        } else {
            ll amount = rnd.next(1LL, min(balance, 200000LL));
            addWithdrawal(log, balance, amount, unit);
        }
    }
}

void makeRandomBounded(vector<Entry>& log) {
    int n = rnd.next(1, 25);
    vector<ll> specialA = {-LIMIT, -1000000000LL, -1LL, 1LL, 1000000000LL, LIMIT};
    vector<ll> specialB = {0LL, 1LL, 9999LL, 1000000000LL, LIMIT};

    for (int i = 0; i < n; ++i) {
        ll a;
        if (rnd.next(0, 4) == 0) {
            a = rnd.any(specialA);
        } else {
            ll magnitude = randAmount(rnd.next(1, 1000000));
            a = rnd.next(0, 1) ? magnitude : -magnitude;
        }

        ll b;
        if (rnd.next(0, 5) == 0) {
            b = rnd.any(specialB);
        } else {
            b = rnd.next(0LL, rnd.next(0, 1) ? 1000000LL : LIMIT);
        }
        log.push_back({a, b});
    }
}

void makeGcdStress(vector<Entry>& log) {
    ll balance = 0;
    ll unit = rnd.next(2LL, 1000000LL);
    int n = rnd.next(3, 18);

    addDeposit(log, balance, rnd.next(1LL, unit * 2));
    for (int i = 1; i < n; ++i) {
        if (rnd.next(0, 2) == 0) {
            addDeposit(log, balance, rnd.next(1LL, 200000LL));
        } else {
            ll target = rnd.next(0LL, unit - 1);
            ll amount = balance + rnd.next(1LL, unit * 4) - target;
            if (amount <= 0) amount = balance + rnd.next(1LL, unit);
            addWithdrawal(log, balance, amount, unit);
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Entry> log;
    int mode = rnd.next(0, 5);
    if (mode <= 2) {
        makeConsistent(log);
    } else if (mode == 3) {
        makeGcdStress(log);
    } else {
        makeRandomBounded(log);
    }

    println((int)log.size());
    for (const Entry& e : log) {
        println(e.a, e.b);
    }

    return 0;
}
