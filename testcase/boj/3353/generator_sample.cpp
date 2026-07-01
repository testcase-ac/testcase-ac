#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 9);
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 6) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 30);
    }

    vector<int> bottom(n), top(n);
    int startBottom = rnd.next(0, 1000000 - 3 * n);
    int startTop = rnd.next(0, 1000000 - 3 * n);
    int bottomStep = rnd.next(1, 3);
    int topStep = rnd.next(1, 3);

    for (int i = 0; i < n; ++i) {
        bottom[i] = startBottom + bottomStep * i;
        top[i] = startTop + topStep * i;
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }

    int mode = n == 1 ? 0 : rnd.next(0, 5);
    if (mode == 0) {
        // Already increasing.
    } else if (mode == 1) {
        reverse(order.begin(), order.end());
    } else if (mode == 2) {
        shuffle(order.begin(), order.end());
    } else if (mode == 3) {
        int block = rnd.next(2, min(n, 6));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            reverse(order.begin() + l, order.begin() + r);
        }
    } else if (mode == 4) {
        vector<int> zigzag;
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            if (rnd.next(0, 1) == 0) {
                zigzag.push_back(lo++);
                if (lo <= hi) {
                    zigzag.push_back(hi--);
                }
            } else {
                zigzag.push_back(hi--);
                if (lo <= hi) {
                    zigzag.push_back(lo++);
                }
            }
        }
        order = zigzag;
    } else {
        int pivot = rnd.next(0, n - 1);
        reverse(order.begin(), order.begin() + pivot + 1);
        shuffle(order.begin() + pivot + 1, order.end());
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(bottom[i], top[order[i]]);
    }

    return 0;
}
