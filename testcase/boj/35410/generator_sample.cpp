#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> t;

    if (mode == 0) {
        n = 1;
        t.push_back(rnd.next(1, 100000));
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        int value = rnd.next(1, 100000);
        t.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        int lo = rnd.next(1, 30);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(0, 20)));
        for (int i = 0; i < n; ++i) {
            t.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 40);
        int cur = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            cur = min(100000, cur + rnd.next(0, 5));
            t.push_back(cur);
        }
        if (rnd.next(0, 1)) {
            reverse(t.begin(), t.end());
        }
    } else if (mode == 4) {
        n = rnd.next(2, 40);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                t.push_back(rnd.next(1, 5));
            } else {
                t.push_back(rnd.next(99995, 100000));
            }
        }
    } else if (mode == 5) {
        n = rnd.next(2, 50);
        int bucketCount = rnd.next(2, 7);
        vector<int> buckets;
        for (int i = 0; i < bucketCount; ++i) {
            buckets.push_back(rnd.next(1, 100000));
        }
        for (int i = 0; i < n; ++i) {
            int value = rnd.any(buckets);
            int delta = rnd.next(-2, 2);
            t.push_back(max(1, min(100000, value + delta)));
        }
    } else {
        n = rnd.next(2, 60);
        int upper = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            t.push_back(rnd.next(1, upper));
        }
    }

    shuffle(t.begin(), t.end());

    println(n);
    println(t);

    return 0;
}
