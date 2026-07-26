#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int q = rnd.next(1, 12);
    int mode = rnd.next(0, 4);
    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        if (mode == 0) a[i] = rnd.next(1, 100);
        if (mode == 1) a[i] = rnd.next(1, 2);
        if (mode == 2) a[i] = 1 << rnd.next(0, 29);
        if (mode == 3) a[i] = rnd.next(1, 30) * (1 << rnd.next(0, 20));
        if (mode == 4) a[i] = rnd.next(0, 1) ? rnd.next(1, 10) : rnd.next(100000000, 1000000000);
    }

    if (mode == 0 && rnd.next(0, 1)) sort(a.begin(), a.end());
    if (mode == 1 && rnd.next(0, 1)) reverse(a.begin(), a.end());

    println(n, q);
    println(a);
    for (int i = 0; i < q; ++i) {
        int l = rnd.next(1, n);
        int r = rnd.next(l, n);
        println(l, r);
    }
}
