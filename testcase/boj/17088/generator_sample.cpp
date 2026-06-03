#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long chooseStart(int n, long long diff) {
    long long lo = 1;
    long long hi = 1000000000LL;
    if (diff > 0) {
        hi -= diff * (n - 1);
    } else {
        lo -= diff * (n - 1);
    }
    return rnd.next(lo, hi);
}

vector<long long> makeProgression(int n, long long diff) {
    long long start = chooseStart(n, diff);
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = start + diff * i;
    }
    return a;
}

void applySmallNoise(vector<long long>& a, int requiredChanges) {
    vector<int> order(a.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    int changed = 0;
    for (int idx : order) {
        if (changed >= requiredChanges) {
            break;
        }
        vector<int> candidates;
        if (a[idx] > 1) {
            candidates.push_back(-1);
        }
        if (a[idx] < 1000000000LL) {
            candidates.push_back(1);
        }
        if (candidates.empty()) {
            continue;
        }
        a[idx] += rnd.any(candidates);
        ++changed;
    }

    for (long long& x : a) {
        if (rnd.next(0, 2) == 0) {
            continue;
        }
        if (x == 1) {
            ++x;
        } else if (x == 1000000000LL) {
            --x;
        } else {
            x += rnd.any(vector<int>{-1, 1});
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<long long> b;

    if (mode == 0) {
        n = rnd.next(1, 2);
        b.resize(n);
        for (long long& x : b) {
            x = rnd.next(1LL, 1000000000LL);
        }
    } else if (mode == 1) {
        n = rnd.next(3, 15);
        long long diff = rnd.next(-20LL, 20LL);
        b = makeProgression(n, diff);
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        long long diff = rnd.next(-12LL, 12LL);
        b = makeProgression(n, diff);
        applySmallNoise(b, rnd.next(1, min(n, 8)));
    } else if (mode == 3) {
        n = rnd.next(3, 18);
        long long diff = rnd.next(-8LL, 8LL);
        b = makeProgression(n, diff);
        int idx = rnd.next(0, n - 1);
        long long delta = rnd.any(vector<long long>{-4, -3, 3, 4, 7, -7});
        if (b[idx] + delta < 1 || b[idx] + delta > 1000000000LL) {
            delta = -delta;
        }
        b[idx] += delta;
    } else if (mode == 4) {
        n = rnd.next(3, 12);
        long long diff = rnd.next(-3LL, 3LL);
        b = makeProgression(n, diff);
        if (rnd.next(0, 1) == 0) {
            long long offset = *min_element(b.begin(), b.end()) - 1;
            for (long long& x : b) {
                x -= offset;
            }
        } else {
            long long offset = 1000000000LL - *max_element(b.begin(), b.end());
            for (long long& x : b) {
                x += offset;
            }
        }
        applySmallNoise(b, rnd.next(1, min(n, 5)));
    } else {
        n = rnd.next(20, 60);
        b.resize(n);
        long long center = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            long long x = center + rnd.next(-25LL, 25LL);
            b[i] = min(1000000000LL, max(1LL, x));
        }
    }

    println(n);
    println(b);
    return 0;
}
