#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 24);
    vector<int> p;

    if (mode == 0) {
        n = rnd.next(3, 6);
        for (int i = 0; i < n; ++i) {
            p.push_back(rnd.next(1, 1000));
        }
    } else if (mode == 1) {
        int value = rnd.next(1, 1000);
        p.assign(n, value);
    } else if (mode == 2) {
        int low = rnd.next(1, 5);
        int high = rnd.next(996, 1000);
        for (int i = 0; i < n; ++i) {
            p.push_back(rnd.next(0, 1) == 0 ? low : high);
        }
    } else if (mode == 3) {
        int start = rnd.next(1, 950);
        int step = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            p.push_back(min(1000, start + i * step));
        }
        if (rnd.next(0, 1) == 0) {
            reverse(p.begin(), p.end());
        }
    } else if (mode == 4) {
        int groups = rnd.next(2, 5);
        vector<int> values;
        for (int i = 0; i < groups; ++i) {
            values.push_back(rnd.next(1, 1000));
        }
        sort(values.begin(), values.end());
        for (int i = 0; i < n; ++i) {
            p.push_back(rnd.any(values));
        }
    } else {
        int lo = rnd.next(1, 800);
        int hi = rnd.next(lo, 1000);
        n = rnd.next(12, 40);
        for (int i = 0; i < n; ++i) {
            p.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(p.begin(), p.end());

    println(n);
    println(p);
    return 0;
}
