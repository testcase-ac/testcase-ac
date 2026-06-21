#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int k = rnd.next(1, 30);
    vector<int> p(n);

    if (mode == 0) {
        for (int& x : p) x = rnd.next(1, 100);
        k = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        p.assign(n, rnd.next(101, 700));
        k = rnd.next(1, 25);
    } else if (mode == 2) {
        for (int& x : p) x = 100 * rnd.next(1, 8) + rnd.next(0, 20);
        k = rnd.next(1, 30);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(1, 8) * 100;
            p[i] = base + rnd.next(0, 99);
        }
        k = rnd.next(1, 30);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) p[i] = rnd.next(1, 1000);
        int richest = rnd.next(150, 1000);
        int ties = rnd.next(1, n);
        for (int i = 0; i < ties; ++i) p[i] = richest;
        shuffle(p.begin(), p.end());
        k = rnd.next(1, 20);
    } else {
        n = rnd.next(1, 12);
        p.resize(n);
        for (int& x : p) x = rnd.next(1, 1000000000);
        k = rnd.next(1, 100000);
    }

    println(n, k);
    println(p);

    return 0;
}
