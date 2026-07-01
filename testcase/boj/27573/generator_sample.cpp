#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 2) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 80);
    }

    int l, h;
    if (mode == 0) {
        l = h = 1;
    } else if (mode == 1) {
        l = h = rnd.next(1, n);
    } else if (mode == 2) {
        l = 1;
        h = n;
    } else {
        l = rnd.next(1, n);
        int maxWidth = min(1000, n - l);
        h = l + rnd.next(0, maxWidth);
    }

    vector<int> p(n);
    if (mode == 0) {
        p[0] = rnd.any(vector<int>{-10000, -1, 0, 1, 10000});
    } else if (mode == 1) {
        for (int& x : p) {
            x = rnd.next(-3, 3);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            p[i] = (i % 2 == 0 ? rnd.next(1, 20) : -rnd.next(1, 20));
        }
    } else if (mode == 3) {
        int value = rnd.next(-2, 2);
        fill(p.begin(), p.end(), value);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(-100, 100);
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(0, 4) == 0 ? rnd.next(-10000, 10000) : rnd.next(-10, 10);
        }
    } else if (mode == 6) {
        int block = rnd.next(1, min(10, n));
        for (int i = 0; i < n; ++i) {
            int sign = ((i / block) % 2 == 0) ? 1 : -1;
            p[i] = sign * rnd.next(0, 50);
        }
    } else {
        int balance = rnd.next(-5, 5);
        for (int i = 0; i < n; ++i) {
            p[i] = balance + rnd.next(-15, 15);
        }
    }

    println(n, l, h);
    for (int x : p) {
        println(x);
    }

    return 0;
}
