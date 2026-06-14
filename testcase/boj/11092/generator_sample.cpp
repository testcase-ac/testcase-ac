#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> times;

    if (mode == 0) {
        n = rnd.next(2, 3);
        int fast = rnd.next(1, 20);
        int slow = rnd.next(fast, 5000);
        times.push_back(fast);
        times.push_back(slow);
        if (n == 3) times.push_back(rnd.next(fast, slow));
    } else if (mode == 1) {
        n = rnd.next(4, 8);
        int base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) times.push_back(base + rnd.next(0, 3));
    } else if (mode == 2) {
        n = rnd.next(4, 15);
        int cur = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 25);
            times.push_back(min(cur, 5000));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 15);
        times.push_back(1);
        times.push_back(rnd.next(1, 5));
        for (int i = 2; i < n; ++i) times.push_back(rnd.next(3000, 5000));
    } else if (mode == 4) {
        n = 15;
        for (int i = 0; i < n; ++i) times.push_back(rnd.next(1, 5000));
    } else {
        n = rnd.next(4, 12);
        int lo = rnd.next(1, 200);
        int hi = rnd.next(lo, 5000);
        for (int i = 0; i < n; ++i) times.push_back(rnd.next(lo, hi));
    }

    shuffle(times.begin(), times.end());
    times.insert(times.begin(), n);
    println(times);

    return 0;
}
