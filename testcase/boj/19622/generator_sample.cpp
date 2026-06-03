#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2;
    } else if (mode == 2) {
        n = rnd.next(3, 6);
    } else {
        n = rnd.next(7, 15);
    }

    int gap;
    if (mode == 3) {
        gap = rnd.next(2, 4);
    } else {
        gap = rnd.next(5, 30);
    }

    int maxSpan = (n + 2) * gap + 10;
    int base;
    if (mode == 4) {
        base = 2147483647 - maxSpan - rnd.next(0, 100);
    } else {
        base = rnd.next(0, 1000);
    }

    vector<int> start(n), finish(n), people(n);
    for (int i = 0; i < n; ++i) {
        start[i] = base + i * gap;
    }

    for (int i = 0; i + 1 < n; ++i) {
        finish[i] = start[i + 1] + rnd.next(1, gap - 1);
    }
    finish[n - 1] = start[n - 1] + gap;

    int valueMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        if (valueMode == 0) {
            people[i] = rnd.next(1, 20);
        } else if (valueMode == 1) {
            people[i] = (i % 2 == 0 ? rnd.next(700, 1000) : rnd.next(1, 60));
        } else if (valueMode == 2) {
            people[i] = (i % 2 == 1 ? rnd.next(700, 1000) : rnd.next(1, 60));
        } else {
            people[i] = rnd.next(1, 1000);
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(start[i], finish[i], people[i]);
    }

    return 0;
}
