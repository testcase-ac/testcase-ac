#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 7);
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 7);
        a.assign(n, 1);
    } else if (mode == 1) {
        n = rnd.next(1, 7);
        a.assign(n, 9);
    } else if (mode == 2) {
        n = rnd.next(2, 7);
        int ones = rnd.next(1, n - 1);
        a.assign(ones, 1);
        while ((int)a.size() < n) {
            a.push_back(rnd.any(vector<int>{7, 8, 9}));
        }
    } else if (mode == 3) {
        n = rnd.next(1, 7);
        int lo = rnd.next(1, 5);
        int hi = rnd.next(lo, 9);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 7);
        vector<int> pool = {2, 2, 3, 3, 4, 5, 6, 8, 9};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else {
        n = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) {
            int value = rnd.wnext(9, rnd.next(-2, 2)) + 1;
            a.push_back(value);
        }
    }

    if (rnd.next(0, 1)) {
        sort(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
