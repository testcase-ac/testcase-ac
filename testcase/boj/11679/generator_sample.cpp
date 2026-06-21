#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeCase(int mode, int n) {
    vector<int> a;

    if (mode == 0) {
        int value = rnd.next(1, 30);
        a.assign(n, value);
    } else if (mode == 1) {
        int low = rnd.next(1, 8);
        int high = rnd.next(50000, 100000);
        for (int i = 0; i < n; ++i) {
            a.push_back((i % 3 == 0) ? high : rnd.next(low, low + 10));
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(min(100000, base + rnd.next(0, 3)));
        }
    } else if (mode == 3) {
        int value = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            a.push_back(value);
            value = min(100000, value * rnd.next(2, 3));
        }
    } else {
        int upper = rnd.next(10, 100000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, upper));
        }
    }

    shuffle(a.begin(), a.end());
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n;
        if (tc == 0 && rnd.next(0, 4) == 0) {
            n = 1;
        } else if (mode == 3) {
            n = rnd.next(2, 10);
        } else {
            n = rnd.next(2, 18);
        }

        vector<int> a = makeCase(mode, n);
        println(n);
        println(a);
    }

    return 0;
}
