#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(1, 10);
    } else if (mode == 2) {
        n = rnd.next(5, 18);
        m = rnd.next(n, 2 * n);
    } else if (mode == 3) {
        n = rnd.next(6, 25);
        m = rnd.next(8, 30);
    } else if (mode == 4) {
        n = rnd.next(20, 60);
        m = rnd.next(20, 70);
    } else {
        n = rnd.next(2, 15);
        m = rnd.next(1, 25);
    }

    vector<int> h(n);
    int heightMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        if (heightMode == 0) {
            h[i] = rnd.next(-5, 5);
        } else if (heightMode == 1) {
            h[i] = (i % 2 == 0 ? -10000 : 10000);
        } else if (heightMode == 2) {
            h[i] = rnd.next(-10000, 10000);
        } else {
            h[i] = i - n / 2;
        }
    }

    println(n, m);
    println(h);

    for (int i = 0; i < m; ++i) {
        int a;
        int b;
        int k;

        if (mode == 0) {
            a = b = 1;
        } else if (mode == 1) {
            if (i % 3 == 0) {
                a = 1;
                b = n;
            } else {
                a = b = rnd.next(1, n);
            }
        } else if (mode == 2) {
            int center = rnd.next(1, n);
            int radius = rnd.next(0, min(center - 1, n - center));
            a = center - radius;
            b = center + radius;
        } else if (mode == 3) {
            a = rnd.next(1, n);
            b = rnd.next(a, min(n, a + rnd.next(0, 5)));
        } else if (mode == 4) {
            a = rnd.next(1, n);
            b = rnd.next(a, n);
        } else {
            int len = rnd.next(1, n);
            a = rnd.next(1, n - len + 1);
            b = a + len - 1;
        }

        int signMode = rnd.next(0, 6);
        if (signMode == 0) {
            k = 0;
        } else if (signMode <= 2) {
            k = rnd.next(-3, 3);
        } else if (signMode == 3) {
            k = 100;
        } else if (signMode == 4) {
            k = -100;
        } else {
            k = rnd.next(-100, 100);
        }

        println(a, b, k);
    }

    return 0;
}
