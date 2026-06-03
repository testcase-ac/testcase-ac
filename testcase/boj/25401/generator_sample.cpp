#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_X = -1000000;
const int MAX_X = 1000000;

int randomValue() {
    return rnd.next(MIN_X, MAX_X);
}

int chooseN(int mode) {
    if (mode == 0) return rnd.next(2, 8);
    if (mode == 1) return rnd.next(9, 40);
    if (mode == 2) return rnd.next(41, 120);
    return rnd.next(121, 500);
}

vector<int> makeProgression(int n, bool forceFlat) {
    int maxAbsDiff = min(2000000 / max(1, n - 1), 4000);
    int diff = forceFlat ? 0 : rnd.next(-maxAbsDiff, maxAbsDiff);
    int lo = MIN_X;
    int hi = MAX_X;

    if (diff > 0) {
        hi = MAX_X - diff * (n - 1);
    } else if (diff < 0) {
        lo = MIN_X - diff * (n - 1);
    }

    int first = rnd.next(lo, hi);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = first + diff * i;
    }
    return a;
}

void perturb(vector<int>& a, int changes) {
    vector<int> order(a.size());
    for (int i = 0; i < int(a.size()); ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    for (int i = 0; i < changes; ++i) {
        int at = order[i];
        int next = a[at];
        while (next == a[at]) {
            if (rnd.next(3) == 0) {
                int delta = rnd.any(vector<int>{-101, -17, -1, 1, 17, 101});
                next = max(MIN_X, min(MAX_X, a[at] + delta));
            } else {
                next = randomValue();
            }
        }
        a[at] = next;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = chooseN(mode % 4);
    vector<int> a;

    if (mode == 0) {
        a = makeProgression(n, false);
    } else if (mode == 1) {
        a = makeProgression(n, true);
        perturb(a, rnd.next(1, max(1, n / 3)));
    } else if (mode == 2) {
        a = makeProgression(n, false);
        perturb(a, rnd.next(1, max(1, min(n - 1, n / 2))));
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        a.assign(n, 0);
        for (int i = 0; i < n; ++i) a[i] = randomValue();
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        a = makeProgression(n, false);
        reverse(a.begin(), a.end());
        perturb(a, rnd.next(0, max(0, n / 4)));
    } else if (mode == 5) {
        n = rnd.next(2, 20);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(vector<int>{MIN_X, MIN_X + 1, -1, 0, 1, MAX_X - 1, MAX_X});
        }
    } else if (mode == 6) {
        n = rnd.next(2, 60);
        a = makeProgression(n, false);
        int anchor = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            if (i != anchor && rnd.next(100) < 45) a[i] = randomValue();
        }
    } else {
        n = rnd.next(250, 500);
        a = makeProgression(n, rnd.next(4) == 0);
        perturb(a, rnd.next(1, 12));
    }

    println(n);
    println(a);
    return 0;
}
