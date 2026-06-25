#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

array<int, 5> randomPermutation() {
    array<int, 5> p = {1, 2, 3, 4, 5};
    shuffle(p.begin(), p.end());
    return p;
}

array<int, 5> rotationPermutation(int shift) {
    array<int, 5> p{};
    for (int i = 0; i < 5; ++i) {
        p[i] = (i + shift) % 5 + 1;
    }
    return p;
}

void printPermutation(const array<int, 5>& p) {
    println(p[0], p[1], p[2], p[3], p[4]);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 12);
    int q = rnd.next(1, 12);

    println(n);
    for (int i = 0; i < n; ++i) {
        array<int, 5> p;
        if (mode == 0 && rnd.next(100) < 35) {
            p = {1, 2, 3, 4, 5};
        } else if (mode == 1) {
            p = rotationPermutation(rnd.next(0, 4));
        } else if (mode == 2 && rnd.next(100) < 50) {
            p = {5, 4, 3, 2, 1};
        } else {
            p = randomPermutation();
        }
        printPermutation(p);
    }

    println(q);
    for (int qi = 0; qi < q; ++qi) {
        int a = 1;
        int b = n;
        int u = rnd.next(1, n);

        if (mode == 0) {
            a = u;
            b = u;
        } else if (mode == 1) {
            a = rnd.next(1, u);
            b = rnd.next(u, n);
        } else if (mode == 2) {
            int len = rnd.next(1, min(5, n));
            a = rnd.next(1, n - len + 1);
            b = a + len - 1;
            u = rnd.next(a, b);
        } else if (mode == 3) {
            if (rnd.next(2) == 0) {
                a = 1;
                b = u;
            } else {
                a = u;
                b = n;
            }
        } else {
            a = rnd.next(1, n);
            b = rnd.next(a, n);
            u = rnd.next(a, b);
        }

        array<int, 5> y;
        if (mode == 1 && rnd.next(100) < 45) {
            y = rotationPermutation(rnd.next(0, 4));
        } else if (mode == 3 && rnd.next(100) < 30) {
            y = {1, 2, 3, 4, 5};
        } else {
            y = randomPermutation();
        }

        printf("%d %d %d %d %d %d %d %d\n", u, a, b, y[0], y[1], y[2], y[3], y[4]);
    }

    return 0;
}
