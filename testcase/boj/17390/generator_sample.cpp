#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 30);
    int q = rnd.next(1, 40);
    int valueMode = rnd.next(0, 4);
    int queryMode = rnd.next(0, 4);

    vector<int> a(n);
    if (valueMode == 0) {
        int x = rnd.next(1, 1000);
        fill(a.begin(), a.end(), x);
    } else if (valueMode == 1) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 5);
    } else if (valueMode == 2) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(996, 1000);
    } else if (valueMode == 3) {
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? 1 : 1000);
        shuffle(a.begin(), a.end());
    } else {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 1000);
    }

    println(n, q);
    println(a);

    for (int i = 0; i < q; ++i) {
        int l, r;
        if (queryMode == 0) {
            l = 1;
            r = n;
        } else if (queryMode == 1) {
            l = r = rnd.next(1, n);
        } else if (queryMode == 2) {
            l = rnd.next(1, n);
            r = rnd.next(l, min(n, l + 4));
        } else if (queryMode == 3) {
            r = rnd.next(1, n);
            l = rnd.next(max(1, r - 4), r);
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }
        println(l, r);
    }

    return 0;
}
