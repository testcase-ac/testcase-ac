#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    int m = rnd.next(1, 24);
    int k = rnd.next(1, m);
    vector<int> a, d;

    if (mode == 0) {
        k = rnd.next(1, min(m, 5));
        a.assign(n, 0);
        d.assign(m, 0);
        for (int& x : a) x = rnd.next(1, 4);
        for (int& x : d) x = rnd.next(0, 1);
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        m = rnd.next(max(2, n), 24);
        k = rnd.next(1, min(m, 3));
        a.assign(n, 1);
        d.assign(m, 0);
        for (int& x : d) x = rnd.next(0, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 18);
        m = rnd.next(10, 30);
        k = rnd.next(1, min(m, 4));
        a.assign(n, 2);
        d.assign(m, 0);
        for (int i = 0; i < n; ++i)
            if (rnd.next(0, 3) == 0) a[i] = rnd.next(3, 6);
        for (int& x : d) x = rnd.next(1, n + 3);
    } else if (mode == 3) {
        n = rnd.next(1, 8);
        m = rnd.next(8, 28);
        k = rnd.next(max(1, m - 5), m);
        a.assign(n, 0);
        d.assign(m, 0);
        for (int& x : a) x = rnd.next(20, 200000);
        for (int& x : d) x = rnd.next(0, 3);
    } else if (mode == 4) {
        n = rnd.next(8, 20);
        m = rnd.next(12, 32);
        k = 1;
        a.assign(n, 0);
        d.assign(m, 0);
        for (int& x : a) x = rnd.next(1, 3);
        for (int& x : d) x = rnd.next(0, 200000);
    } else {
        a.assign(n, 0);
        d.assign(m, 0);
        for (int& x : a) x = rnd.next(1, 12);
        for (int& x : d) x = rnd.next(0, 12);
    }

    shuffle(a.begin(), a.end());
    shuffle(d.begin(), d.end());

    println(n, k, m);
    println(a);
    println(d);

    return 0;
}
