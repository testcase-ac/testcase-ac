#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;

    if (mode == 0) {
        n = 0;
        m = rnd.next(1, 999);
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = n + 1;
    } else if (mode == 2) {
        n = rnd.next(1, 10);
        m = rnd.next(n + 20, min(999, n + 160));
    } else if (mode == 3) {
        n = rnd.next(1, 25);
        m = rnd.next(n + 1, min(999, n + 80));
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        m = rnd.next(n + 1, min(999, n + 120));
    } else {
        n = rnd.next(1, 998);
        m = rnd.next(n + 1, 999);
    }

    vector<int> h(n);
    int pattern = rnd.next(5);
    for (int i = 0; i < n; ++i) {
        if (pattern == 0) {
            h[i] = rnd.next(1, 4);
        } else if (pattern == 1) {
            h[i] = rnd.next(95, 99);
        } else if (pattern == 2) {
            h[i] = (i % 2 == 0 ? rnd.next(1, 5) : rnd.next(80, 99));
        } else if (pattern == 3) {
            h[i] = rnd.next(1, 99);
        } else {
            int center = rnd.next(20, 80);
            h[i] = max(1, min(99, center + rnd.next(-10, 10)));
        }
    }

    println(n, m);
    println(h);

    return 0;
}
