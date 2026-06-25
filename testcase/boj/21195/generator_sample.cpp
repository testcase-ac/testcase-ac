#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(2, 12);
    }

    long long maxS = 100000000LL;
    if (n > 1) {
        maxS /= (n - 1);
    }

    long long s;
    if (mode == 1) {
        s = 1;
    } else if (mode == 2) {
        s = maxS;
    } else {
        s = rnd.next(1LL, maxS);
    }

    long long base = s * (n - 1LL);
    long long spare = 100000000LL - base;
    vector<long long> credits(n);

    if (mode == 0) {
        credits[0] = rnd.next(1LL, 100000000LL);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            credits[i] = base + rnd.next(0LL, min(30LL, spare));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            credits[i] = base;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            credits[i] = base + rnd.next(0LL, spare);
        }
        credits[rnd.next(0, n - 1)] = base;
    } else if (mode == 4) {
        long long lowExtra = rnd.next(0LL, min(spare, 1000LL));
        long long highExtra = rnd.next(lowExtra, spare);
        for (int i = 0; i < n; ++i) {
            credits[i] = base + rnd.next(lowExtra, highExtra);
        }
    } else {
        long long step = max(1LL, spare / max(1, n - 1));
        for (int i = 0; i < n; ++i) {
            credits[i] = min(100000000LL, base + step * i + rnd.next(0LL, min(step - 1, 1000LL)));
        }
    }

    if (rnd.next(0, 2) == 0) {
        sort(credits.begin(), credits.end());
    } else if (rnd.next(0, 1) == 0) {
        sort(credits.rbegin(), credits.rend());
    } else {
        shuffle(credits.begin(), credits.end());
    }

    println(n, s);
    for (long long c : credits) {
        println(c);
    }

    return 0;
}
