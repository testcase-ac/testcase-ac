#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int t;
    int s;

    if (mode == 0) {
        n = 1;
        t = rnd.next(1, 12);
        s = rnd.next(0, t);
    } else {
        n = rnd.next(2, 18);
        t = rnd.next(1, 40);
        if (mode == 1) {
            s = 0;
        } else if (mode == 2) {
            s = t;
        } else if (mode == 3) {
            s = t / 2;
        } else {
            s = rnd.next(0, t);
        }
    }

    int before = s;
    int after = t - s;
    int feasibleLimit = max(before, after);

    vector<int> a(n), b(n);
    int guaranteed = rnd.next(0, n - 1);

    for (int i = 0; i < n; ++i) {
        if (i == guaranteed || rnd.next(0, 99) < 70 || feasibleLimit == t) {
            b[i] = rnd.next(1, max(1, feasibleLimit));
        } else {
            b[i] = rnd.next(feasibleLimit + 1, 3000);
        }

        if (mode == 4 && i % 3 == 0) {
            a[i] = rnd.next(90000, 100000);
        } else if (mode == 5 && i % 4 == 0) {
            a[i] = 0;
        } else {
            a[i] = rnd.next(0, 200);
        }
    }

    if (feasibleLimit == 0) {
        t = 1;
        s = rnd.next(0, 1);
        feasibleLimit = max(s, t - s);
    }
    b[guaranteed] = rnd.next(1, max(1, feasibleLimit));

    if (rnd.next(0, 1)) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        vector<int> shuffledA(n), shuffledB(n);
        for (int i = 0; i < n; ++i) {
            shuffledA[i] = a[order[i]];
            shuffledB[i] = b[order[i]];
        }
        a = shuffledA;
        b = shuffledB;
    }

    println(n, t, s);
    for (int i = 0; i < n; ++i) {
        println(a[i], b[i]);
    }

    return 0;
}
