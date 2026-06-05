#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int a;
    int b;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = rnd.next(2, 12);
        a = rnd.next(1, n);
        do {
            b = rnd.next(1, n);
        } while (b == a);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        a = rnd.next(1, n - 1);
        b = a + 1;
        if (rnd.next(0, 1)) swap(a, b);
    } else if (mode == 2) {
        n = rnd.next(3, 60);
        int gap = 1 << rnd.next(1, 5);
        if (gap >= n) gap = n - 1;
        a = rnd.next(1, n - gap);
        b = a + gap;
        if (rnd.next(0, 1)) swap(a, b);
    } else if (mode == 3) {
        n = rnd.next(10, 100);
        a = rnd.next(1, min(n, 5));
        b = rnd.next(max(1, n - 4), n);
        if (a == b) b = n;
        if (rnd.next(0, 1)) swap(a, b);
    } else if (mode == 4) {
        n = rnd.next(20, 200);
        int parity = rnd.next(0, 1);
        a = rnd.next(1, n);
        if ((a & 1) != parity) {
            if (a < n) ++a;
            else --a;
        }
        do {
            b = rnd.next(1, n);
            if ((b & 1) != parity) {
                if (b < n) ++b;
                else --b;
            }
        } while (b == a);
    } else if (mode == 5) {
        n = rnd.next(1000, 500000);
        a = rnd.next(1, 50);
        b = rnd.next(n - 49, n);
        if (rnd.next(0, 1)) swap(a, b);
    } else if (mode == 6) {
        n = 500000;
        a = rnd.next(1, n);
        do {
            b = rnd.next(1, n);
        } while (b == a);
    } else {
        n = rnd.next(31, 500);
        int maxDay = 1;
        while ((1 << maxDay) * 2 < n) ++maxDay;
        int day = rnd.next(1, maxDay);
        int jump = 1 << (day - 1);
        int meet = rnd.next(jump + 1, n - jump);
        a = meet - jump;
        b = meet + jump;
        if (rnd.next(0, 1)) swap(a, b);
    }

    println(n, a, b);
    return 0;
}
