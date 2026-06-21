#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 35);
    vector<int> xs(n + 1), ys(n + 1);

    for (int i = 1; i <= n; ++i) {
        int x = 0;
        if (mode == 0) {
            x = i - 1;
        } else if (mode == 1) {
            int cap = min(i - 1, rnd.next(0, 7));
            x = rnd.next(0, cap);
        } else if (mode == 2) {
            x = rnd.next(0, i - 1);
        } else if (mode == 3) {
            x = rnd.next(0, i - 1);
        } else {
            x = (rnd.next(0, 3) == 0 ? i - 1 : rnd.next(0, i - 1));
        }

        int y = 0;
        if (mode == 2) {
            y = rnd.next(0, 1) == 0 ? 0 : x + 1;
        } else if (mode == 3) {
            int bias = rnd.next(0, 4);
            if (bias == 0) {
                y = 0;
            } else if (bias == 1) {
                y = x + 1;
            } else if (bias == 2) {
                y = (x + 1) / 2;
            } else {
                y = rnd.next(0, x + 1);
            }
        } else {
            y = rnd.next(0, x + 1);
        }

        xs[i] = x;
        ys[i] = y;
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(xs[i], ys[i]);
    }

    return 0;
}
