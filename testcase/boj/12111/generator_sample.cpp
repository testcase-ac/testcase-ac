#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.wnext(8, -2) + 1;
    if (mode == 3 && rnd.next(4) == 0) {
        n = rnd.next(9, 12);
    }

    int count = 1 << n;
    vector<int> a(count);

    if (mode == 0) {
        int value = rnd.next(1, 1000000000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int start = rnd.next(1, 1000000000 - count + 1);
        int step = rnd.next(1, max(1, (1000000000 - start) / max(1, count)));
        for (int i = 0; i < count; ++i) {
            a[i] = start + i * step;
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        int classes = rnd.next(1, min(count, 8));
        vector<int> values(classes);
        int current = rnd.next(1, 20);
        for (int i = 0; i < classes; ++i) {
            current += rnd.next(0, 7);
            values[i] = min(current, 1000000000);
        }
        for (int i = 0; i < count; ++i) {
            a[i] = rnd.any(values);
        }
    } else if (mode == 3) {
        for (int i = 0; i < count; ++i) {
            int bucket = rnd.next(4);
            if (bucket == 0) {
                a[i] = 1;
            } else if (bucket == 1) {
                a[i] = 2;
            } else if (bucket == 2) {
                a[i] = 1000000000 - rnd.next(0, min(1000, count));
            } else {
                a[i] = rnd.next(1, 1000000000);
            }
        }
    } else {
        int block = 1 << rnd.next(0, n);
        int value = rnd.next(1, 50);
        for (int i = 0; i < count; ++i) {
            if (i % block == 0) {
                value += rnd.next(0, 5);
            }
            a[i] = value;
        }
        if (rnd.next(2) == 0) {
            reverse(a.begin(), a.end());
        }
        if (rnd.next(2) == 0) {
            shuffle(a.begin(), a.end());
        }
    }

    println(n);
    println(a);
    return 0;
}
