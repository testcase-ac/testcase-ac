#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_A = 1000000000LL;

long long clampAmount(long long value) {
    return max(1LL, min(MAX_A, value));
}

vector<long long> makeAmounts(int n, long long x, int mode) {
    vector<long long> a;
    a.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1LL, x));
        }
    } else if (mode == 1) {
        long long maxRounds = max(1LL, MAX_A / x);
        long long roundsHi = min(maxRounds, 8LL);
        for (int i = 0; i < n; ++i) {
            long long rounds = rnd.next(1LL, roundsHi);
            long long delta = rnd.next(0LL, min(x - 1, 3LL));
            a.push_back(clampAmount(rounds * x - delta));
        }
    } else if (mode == 2) {
        long long maxRounds = max(1LL, MAX_A / x);
        long long roundsHi = min(maxRounds, 12LL);
        for (int i = 0; i < n; ++i) {
            long long rounds = i % 2 == 0 ? 1 : rnd.next(2LL, max(2LL, roundsHi));
            long long offset = rnd.next(0LL, min(x - 1, 20LL));
            a.push_back(clampAmount((rounds - 1) * x + 1 + offset));
        }
    } else if (mode == 3) {
        int groups = rnd.next(1, min(n, 6));
        vector<long long> groupRounds;
        long long maxRounds = max(1LL, MAX_A / x);
        for (int i = 0; i < groups; ++i) {
            groupRounds.push_back(rnd.next(1LL, min(maxRounds, 20LL)));
        }
        for (int i = 0; i < n; ++i) {
            long long rounds = groupRounds[i % groups];
            long long low = (rounds - 1) * x + 1;
            long long high = min(rounds * x, MAX_A);
            a.push_back(rnd.next(low, high));
        }
    } else {
        long long maxRounds = max(1LL, MAX_A / x);
        for (int i = 0; i < n; ++i) {
            long long rounds;
            if (i % 5 == 0) {
                rounds = maxRounds;
            } else if (i % 5 == 1) {
                rounds = 1;
            } else {
                rounds = rnd.next(1LL, min(maxRounds, 1000LL));
            }
            long long low = (rounds - 1) * x + 1;
            long long high = min(rounds * x, MAX_A);
            a.push_back(rnd.next(low, high));
        }
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(a.begin(), a.end());
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 16);
    int largeCases = rnd.next(0, min(3, t));
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 4);
        int n;
        if (tc < largeCases) {
            n = rnd.next(101, 180);
        } else if (mode == 0) {
            n = rnd.next(1, 12);
        } else {
            n = rnd.next(2, 40);
        }

        long long x;
        if (mode == 4) {
            x = rnd.any(vector<long long>{1LL, 2LL, 999999937LL, 1000000000LL});
        } else {
            x = rnd.next(1LL, 1000000000LL);
        }

        vector<long long> a = makeAmounts(n, x, mode);
        println(n, x);
        println(a);
    }

    return 0;
}
