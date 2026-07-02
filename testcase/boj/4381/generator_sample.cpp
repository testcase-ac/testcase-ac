#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> times;

    if (mode == 0) {
        int n = rnd.next(1, 6);
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, min(100, lo + rnd.next(0, 25)));
        for (int i = 0; i < n; ++i) {
            times.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 14);
        vector<int> pool;
        int poolSize = rnd.next(1, 5);
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(rnd.next(1, 100));
        }
        for (int i = 0; i < n; ++i) {
            times.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        int n = rnd.next(4, 18);
        times.push_back(rnd.next(1, 3));
        times.push_back(rnd.next(2, 8));
        for (int i = 2; i < n; ++i) {
            times.push_back(rnd.next(60, 100));
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 20);
        int a = rnd.next(1, 15);
        int b = rnd.next(a, min(100, a + 20));
        times.push_back(a);
        times.push_back(b);
        for (int i = 2; i < n; ++i) {
            int nearBoundary = 2 * b - a + rnd.next(-4, 4);
            times.push_back(max(1, min(100, nearBoundary + rnd.next(-8, 12))));
        }
    } else if (mode == 4) {
        int n = rnd.next(15, 45);
        for (int i = 0; i < n; ++i) {
            times.push_back(rnd.wnext(100, 2) + 1);
        }
    } else {
        int n = rnd.next(35, 80);
        for (int i = 0; i < n; ++i) {
            times.push_back(rnd.next(1, 100));
        }
    }

    int order = rnd.next(0, 3);
    if (order == 0) {
        sort(times.begin(), times.end());
    } else if (order == 1) {
        sort(times.rbegin(), times.rend());
    } else {
        shuffle(times.begin(), times.end());
    }

    println(static_cast<int>(times.size()));
    for (int time : times) {
        println(time);
    }

    return 0;
}
