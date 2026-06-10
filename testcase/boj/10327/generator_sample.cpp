#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> fib = {1, 1};
    while (fib.back() <= 1000000000 - fib[fib.size() - 2]) {
        fib.push_back(fib.back() + fib[fib.size() - 2]);
    }

    int mode = rnd.next(0, 5);
    int t = rnd.next(1, 100);
    vector<int> values;

    auto addValue = [&](int x) {
        values.push_back(max(2, min(1000000000, x)));
    };

    if (mode == 0) {
        t = rnd.next(1, 25);
        int start = rnd.next(2, 120);
        for (int i = 0; i < t; ++i) addValue(start + i);
    } else if (mode == 1) {
        t = rnd.next(20, 100);
        for (int i = 0; i < t; ++i) addValue(rnd.next(2, 1000));
    } else if (mode == 2) {
        t = rnd.next(10, 80);
        for (int i = 0; i < t; ++i) {
            int f = fib[rnd.next(2, (int)fib.size() - 1)];
            int delta = rnd.next(-5, 5);
            addValue(f + delta);
        }
    } else if (mode == 3) {
        t = rnd.next(10, 80);
        for (int i = 0; i < t; ++i) {
            int f = fib[rnd.next(2, (int)fib.size() - 1)];
            int multiplier = rnd.next(1, max(1, 1000000000 / f));
            addValue(f * multiplier);
        }
    } else if (mode == 4) {
        t = rnd.next(5, 40);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 3) == 0) {
                addValue(1000000000 - rnd.next(0, 10000));
            } else {
                addValue(rnd.next(2, 1000000000));
            }
        }
    } else {
        t = rnd.next(8, 60);
        vector<int> anchors = {2, 3, 4, 5, 8, 13, 89, 123, 1000, 1573655, 842831057, 1000000000};
        shuffle(anchors.begin(), anchors.end());
        for (int x : anchors) {
            if ((int)values.size() == t) break;
            addValue(x);
        }
        while ((int)values.size() < t) {
            int base = rnd.next(0, 1) ? rnd.any(anchors) : rnd.next(2, 1000000000);
            addValue(base + rnd.next(-20, 20));
        }
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int x : values) println(x);

    return 0;
}
