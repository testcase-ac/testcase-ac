#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int c;
    if (mode == 0) {
        c = 1;
    } else if (mode == 1) {
        c = rnd.next(2, 5);
    } else if (mode == 2) {
        c = rnd.next(6, 15);
    } else if (mode == 3) {
        c = rnd.next(16, 40);
    } else if (mode == 4) {
        c = rnd.next(100, 1000);
    } else {
        c = rnd.next(4587000, 4587520);
    }

    int n = rnd.next(1, mode == 5 ? 10000 : 25);
    int o = rnd.next(8, mode == 5 ? 20 : 35);

    println(c, n, o);

    vector<int> touched;
    touched.push_back(0);
    touched.push_back(c - 1);
    if (c > 2) touched.push_back(c / 2);

    for (int i = 0; i < o; ++i) {
        int kind;
        if (i == 0) {
            kind = 2;
        } else if (i % 7 == 0) {
            kind = rnd.next(0, 1);
        } else {
            kind = rnd.next(0, 2);
        }

        if (kind == 2) {
            int x = rnd.any(touched);
            if (rnd.next(0, 3) == 0) x = rnd.next(0, c - 1);
            println("state", x);
            continue;
        }

        int s;
        int sign = rnd.next(0, 1) == 0 ? -1 : 1;
        if (i % 5 == 1) {
            s = sign * n;
        } else if (i % 11 == 3) {
            s = 0;
        } else {
            s = sign * rnd.next(1, n);
        }

        if (kind == 0) {
            int x = rnd.next(0, c - 1);
            if (rnd.next(0, 4) == 0) x = rnd.any(touched);
            println("change", x, s);
            continue;
        }

        int a;
        int b;
        int rangeMode = rnd.next(0, 4);
        if (rangeMode == 0) {
            a = 0;
            b = c - 1;
        } else if (rangeMode == 1) {
            a = rnd.next(0, c - 1);
            b = a;
        } else if (rangeMode == 2 && c > 1) {
            int width = rnd.next(1, min(c, 8));
            a = rnd.next(0, c - width);
            b = a + width - 1;
        } else {
            a = rnd.next(0, c - 1);
            b = rnd.next(0, c - 1);
            if (a > b) swap(a, b);
        }
        println("groupchange", a, b, s);
    }
}
