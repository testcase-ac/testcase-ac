#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N = 1000000;

int clampN(int value) {
    return max(1, min(MAX_N, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> fib = {1, 2};
    while (fib.back() + fib[fib.size() - 2] <= MAX_N) {
        fib.push_back(fib.back() + fib[fib.size() - 2]);
    }

    vector<int> values;
    auto add = [&](int value) {
        values.push_back(clampN(value));
    };

    int mode = rnd.next(0, 5);
    int t = rnd.next(4, 18);

    if (mode == 0) {
        t = rnd.next(6, 24);
        int upper = rnd.next(8, 120);
        for (int i = 0; i < t; ++i) {
            add(rnd.next(1, upper));
        }
    } else if (mode == 1) {
        t = rnd.next(6, 22);
        int base = rnd.next(1, MAX_N - 1000);
        int window = rnd.next(5, 1000);
        for (int i = 0; i < t; ++i) {
            add(base + rnd.next(0, window));
        }
    } else if (mode == 2) {
        t = rnd.next(8, 24);
        for (int i = 0; i < t; ++i) {
            int p = 1 << rnd.next(0, 19);
            add(p + rnd.next(-3, 3));
        }
    } else if (mode == 3) {
        t = rnd.next(8, 24);
        for (int i = 0; i < t; ++i) {
            int f = rnd.any(fib);
            add(f + rnd.next(-2, 2));
        }
    } else if (mode == 4) {
        t = rnd.next(8, 20);
        vector<int> anchors = {1, 2, 3, 5, 7, 999999, 1000000};
        for (int anchor : anchors) add(anchor);
        while ((int)values.size() < t) {
            int anchor = rnd.any(anchors);
            add(anchor + rnd.next(-10, 10));
        }
    } else {
        t = rnd.next(10, 30);
        for (int i = 0; i < t; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                add(rnd.next(1, 100));
            } else if (bucket == 1) {
                add(rnd.next(101, 10000));
            } else if (bucket == 2) {
                add(rnd.next(10001, 300000));
            } else {
                add(rnd.next(300001, MAX_N));
            }
        }
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int value : values) {
        println(value);
    }

    return 0;
}
