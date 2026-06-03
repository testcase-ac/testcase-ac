#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxSum = 4000000;
    int t = rnd.next(1, 20);
    int remaining = maxSum;
    vector<int> ks;

    for (int i = 0; i < t; ++i) {
        int slotsLeft = t - i;
        int limit = remaining - (slotsLeft - 1);
        int mode = rnd.next(0, 5);
        int k = 1;

        if (mode == 0) {
            k = rnd.next(1, min(limit, 40));
        } else if (mode == 1) {
            int exp = rnd.next(0, 21);
            k = 1 << exp;
            k = min(k, limit);
        } else if (mode == 2) {
            int exp = rnd.next(1, 21);
            int base = 1 << exp;
            int delta = rnd.next(-5, 5);
            k = max(1, base + delta);
            k = min(k, limit);
        } else if (mode == 3) {
            int cap = min(limit, 5000);
            k = rnd.next(1, cap);
        } else if (mode == 4) {
            int low = min(limit, max(1, limit / 2));
            k = rnd.next(low, limit);
        } else {
            int cap = min(limit, 200000);
            k = rnd.wnext(cap, 2) + 1;
        }

        ks.push_back(k);
        remaining -= k;
    }

    shuffle(ks.begin(), ks.end());

    println(t);
    for (int k : ks) {
        println(k);
    }

    return 0;
}
