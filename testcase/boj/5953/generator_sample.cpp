#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int profit(int lo, int hi) {
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    vector<int> p(n);

    if (mode == 0) {
        for (int& x : p) x = profit(-1000, -1);
    } else if (mode == 1) {
        for (int& x : p) x = profit(1, 1000);
    } else if (mode == 2) {
        for (int& x : p) x = rnd.next(0, 3) == 0 ? 0 : profit(-20, 20);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int magnitude = profit(700, 1000);
            p[i] = (i % 2 == rnd.next(0, 1)) ? magnitude : -magnitude;
        }
    } else if (mode == 4) {
        for (int& x : p) x = profit(-60, 30);
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        for (int i = l; i <= r; ++i) p[i] = profit(20, 120);
    } else {
        int valueChoices[] = {-1000, -1, 0, 1, 1000};
        for (int& x : p) x = valueChoices[rnd.next(0, 4)];
    }

    if (rnd.next(0, 3) == 0) shuffle(p.begin(), p.end());

    println(n);
    for (int x : p) println(x);

    return 0;
}
