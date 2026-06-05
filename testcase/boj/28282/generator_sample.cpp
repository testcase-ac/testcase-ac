#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x = rnd.next(1, 24);
    int k = rnd.next(1, 40);
    vector<int> a(2 * x);

    if (mode == 0) {
        int color = rnd.next(1, k);
        fill(a.begin(), a.end(), color);
    } else if (mode == 1 && k >= 2) {
        int split = rnd.next(1, k - 1);
        for (int i = 0; i < x; ++i) a[i] = rnd.next(1, split);
        for (int i = x; i < 2 * x; ++i) a[i] = rnd.next(split + 1, k);
    } else if (mode == 2 && k >= 2) {
        int common = rnd.next(1, k);
        int other = rnd.next(1, k - 1);
        if (other >= common) ++other;
        for (int i = 0; i < x; ++i) {
            a[i] = rnd.next(0, 4) == 0 ? other : common;
        }
        for (int i = x; i < 2 * x; ++i) {
            a[i] = rnd.next(0, 4) == 0 ? other : common;
        }
    } else if (mode == 3) {
        int used = rnd.next(1, min(k, 8));
        for (int i = 0; i < 2 * x; ++i) {
            int bias = rnd.next(0, 5);
            a[i] = bias == 0 ? rnd.next(1, used) : 1;
        }
    } else if (mode == 4) {
        for (int i = 0; i < x; ++i) a[i] = rnd.next(1, k);
        vector<int> left = vector<int>(a.begin(), a.begin() + x);
        for (int i = x; i < 2 * x; ++i) {
            if (rnd.next(0, 2) == 0) {
                a[i] = rnd.any(left);
            } else {
                a[i] = rnd.next(1, k);
            }
        }
    } else {
        for (int i = 0; i < 2 * x; ++i) a[i] = rnd.next(1, k);
    }

    println(x, k);
    println(a);

    return 0;
}
