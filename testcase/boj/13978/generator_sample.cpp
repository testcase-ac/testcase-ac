#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 40);
    int r;
    set<int> cameras;

    if (mode == 0) {
        r = rnd.next(2, n);
    } else if (mode == 1) {
        r = rnd.any(vector<int>{2, n});
    } else {
        r = rnd.next(max(2, n / 4), n);
    }

    if (mode == 0) {
        // No existing cameras.
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            cameras.insert(i);
        }
    } else if (mode == 2) {
        cameras.insert(1);
        cameras.insert(n);
        int extra = rnd.next(0, min(n - 2, 6));
        while ((int)cameras.size() < extra + 2) {
            cameras.insert(rnd.next(2, n - 1));
        }
    } else if (mode == 3) {
        int center = rnd.next(1, n);
        int radius = rnd.next(0, min(5, n - 1));
        for (int x = max(1, center - radius); x <= min(n, center + radius); ++x) {
            if (rnd.next(0, 1) == 1) {
                cameras.insert(x);
            }
        }
        if (cameras.empty()) {
            cameras.insert(center);
        }
    } else if (mode == 4) {
        int step = rnd.next(2, min(n, 7));
        int offset = rnd.next(1, step);
        for (int x = offset; x <= n; x += step) {
            cameras.insert(x);
        }
    } else {
        int k = rnd.next(0, n);
        while ((int)cameras.size() < k) {
            cameras.insert(rnd.next(1, n));
        }
    }

    vector<int> output(cameras.begin(), cameras.end());
    if (rnd.next(0, 1) == 1) {
        shuffle(output.begin(), output.end());
    }

    println(n, (int)output.size(), r);
    for (int x : output) {
        println(x);
    }

    return 0;
}
