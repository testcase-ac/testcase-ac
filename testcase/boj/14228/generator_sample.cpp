#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    long long c;
    vector<int> t;
    vector<int> x;

    if (mode == 0) {
        n = 1;
        c = rnd.next(1, 1000000000);
        t.push_back(rnd.next(1, 1000000));
        x.push_back(rnd.next(1, 1000000));
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        c = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            t.push_back(rnd.next(1, 20));
            x.push_back(rnd.next(1, 30));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        c = 1000000000LL;
        for (int i = 0; i < n; ++i) {
            t.push_back(rnd.next(1, 10000));
            x.push_back(rnd.next(1, 100));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 15);
        c = rnd.next(50, 1000000);
        int start = rnd.next(1, 1000000);
        int step = rnd.next(0, 10000);
        bool increasing = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            t.push_back(rnd.next(1, 5000));
            int value = increasing ? min(1000000, start + i * step)
                                   : max(1, start - i * step);
            x.push_back(value);
        }
    } else if (mode == 4) {
        n = rnd.next(6, 20);
        c = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            bool spike = rnd.next(0, 4) == 0;
            t.push_back(spike ? rnd.next(1, 5) : rnd.next(1000, 1000000));
            x.push_back(spike ? rnd.next(500000, 1000000) : rnd.next(1, 1000));
        }
    } else {
        n = rnd.next(20, 50);
        c = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            t.push_back(rnd.next(900000, 1000000));
            x.push_back(rnd.next(900000, 1000000));
        }
    }

    if (rnd.next(0, 1)) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        vector<int> shuffledT, shuffledX;
        for (int index : order) {
            shuffledT.push_back(t[index]);
            shuffledX.push_back(x[index]);
        }
        t = shuffledT;
        x = shuffledX;
    }

    println(n, c);
    println(t);
    println(x);

    return 0;
}
