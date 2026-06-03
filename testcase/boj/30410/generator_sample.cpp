#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 40);
        a.assign(n, rnd.next(1, 2));
    } else if (mode == 1) {
        n = rnd.next(2, 60);
        int first = rnd.next(1, 2);
        for (int i = 0; i < n; ++i) a.push_back((i % 2 == 0) ? first : 3 - first);
    } else if (mode == 2) {
        int blocks = rnd.next(2, 12);
        int cur = rnd.next(1, 2);
        for (int i = 0; i < blocks; ++i) {
            int len = rnd.next(1, 10);
            for (int j = 0; j < len; ++j) a.push_back(cur);
            if (rnd.next(0, 3) != 0) cur = 3 - cur;
        }
        n = (int)a.size();
    } else if (mode == 3) {
        n = rnd.next(1, 80);
        int onesPrefix = rnd.next(0, n);
        int twosMiddle = rnd.next(0, n - onesPrefix);
        int onesSuffix = n - onesPrefix - twosMiddle;
        for (int i = 0; i < onesPrefix; ++i) a.push_back(1);
        for (int i = 0; i < twosMiddle; ++i) a.push_back(2);
        for (int i = 0; i < onesSuffix; ++i) a.push_back(1);
    } else if (mode == 4) {
        int k = rnd.next(1, 6);
        int repeated = 1 << k;
        int value = rnd.next(1, 2);
        a.assign(repeated, value);
        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) a.insert(a.begin() + rnd.next(0, (int)a.size()), rnd.next(1, 2));
        n = (int)a.size();
    } else {
        n = rnd.next(1, 120);
        int bias = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, 99) < bias ? 1 : 2);
    }

    println(n);
    println(a);

    return 0;
}
