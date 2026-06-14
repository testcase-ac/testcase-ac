#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomArray(int n, int lo, int hi) {
    vector<int> values(n);
    for (int i = 0; i < n; ++i) values[i] = rnd.next(lo, hi);
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(n + 1, n + 8);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = n;
    } else if (mode == 3) {
        n = rnd.next(3, 16);
        m = rnd.next(1, min(n, 4));
    } else if (mode == 4) {
        n = rnd.next(8, 28);
        m = rnd.next(max(1, n / 2 - 2), n);
    } else if (mode == 5) {
        n = rnd.next(4, 20);
        m = rnd.next(1, n);
    } else if (mode == 6) {
        n = rnd.next(10, 40);
        m = rnd.next(1, n);
    } else {
        n = rnd.next(30, 80);
        m = rnd.next(1, n + 20);
    }

    vector<int> a(n);
    vector<int> b(n);

    if (mode == 0) {
        a[0] = rnd.next(1, 500000);
        b[0] = rnd.next(1, 500000);
    } else if (mode == 1) {
        a = randomArray(n, 1, 20);
        b = randomArray(n, 1, 30);
    } else if (mode == 2) {
        int baseA = rnd.next(1, 25);
        int baseB = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            a[i] = baseA + rnd.next(0, 3);
            b[i] = baseB + rnd.next(0, 3);
        }
        a[rnd.next(0, n - 1)] = 500000;
        b[rnd.next(0, n - 1)] = 500000;
    } else if (mode == 3) {
        int low = rnd.next(1, 6);
        int high = rnd.next(50, 200);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? low + rnd.next(0, 3) : high + rnd.next(0, 20);
            b[i] = (i % 2 == 0) ? high + rnd.next(0, 20) : low + rnd.next(0, 3);
        }
    } else if (mode == 4) {
        a = randomArray(n, 1, 40);
        b = randomArray(n, 1, 40);
        int spikes = rnd.next(1, min(n, 5));
        for (int i = 0; i < spikes; ++i) {
            int pos = rnd.next(0, n - 1);
            if (rnd.next(0, 1)) {
                a[pos] = rnd.next(100000, 500000);
            } else {
                b[pos] = rnd.next(100000, 500000);
            }
        }
    } else if (mode == 5) {
        int startA = rnd.next(1, 30);
        int startB = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            a[i] = min(500000, startA + i * rnd.next(1, 5));
            b[i] = min(500000, startB + (n - 1 - i) * rnd.next(1, 5));
        }
    } else if (mode == 6) {
        int block = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            int group = i / block;
            a[i] = 1 + group * rnd.next(1, 4);
            b[i] = 1 + (i % block) * rnd.next(1, 8);
        }
    } else {
        a = randomArray(n, 499000, 500000);
        b = randomArray(n, 499000, 500000);
        if (rnd.next(0, 1)) {
            a[rnd.next(0, n - 1)] = 1;
        } else {
            b[rnd.next(0, n - 1)] = 1;
        }
    }

    println(n, m);
    println(a);
    println(b);

    return 0;
}
