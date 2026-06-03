#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 5) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(3, 15);
    }

    int maxValue = rnd.any(vector<int>{3, 10, 100, 100000});
    vector<int> cross(n), left(n - 1), right(n - 1);

    for (int i = 0; i < n; ++i) {
        cross[i] = rnd.next(1, maxValue);
    }
    for (int i = 0; i + 1 < n; ++i) {
        left[i] = rnd.next(1, maxValue);
        right[i] = rnd.next(1, maxValue);
    }

    if (mode == 1) {
        int target = rnd.next(0, n - 1);
        for (int i = 0; i + 1 < n; ++i) {
            left[i] = (i < target ? 1 : maxValue);
            right[i] = (i < target ? maxValue : 1);
        }
        for (int i = 0; i < n; ++i) {
            cross[i] = rnd.next(1, 5);
        }
    } else if (mode == 2) {
        for (int i = 0; i + 1 < n; ++i) {
            left[i] = right[i] = rnd.next(1, maxValue);
        }
        int sharedCross = rnd.next(1, maxValue);
        for (int i = 0; i < n; ++i) {
            cross[i] = sharedCross;
        }
    } else if (mode == 3) {
        for (int i = 0; i + 1 < n; ++i) {
            left[i] = rnd.next(maxValue / 2 + 1, maxValue);
            right[i] = rnd.next(1, maxValue / 2 + 1);
        }
        for (int i = 0; i < n; ++i) {
            cross[i] = (i % 2 == 0 ? 1 : maxValue);
        }
    } else if (mode == 4) {
        for (int i = 0; i + 1 < n; ++i) {
            left[i] = (i % 2 == 0 ? maxValue : 1);
            right[i] = (i % 2 == 0 ? 1 : maxValue);
        }
        for (int i = 0; i < n; ++i) {
            cross[i] = rnd.next(1, maxValue);
        }
    } else if (mode == 5) {
        for (int i = 0; i + 1 < n; ++i) {
            left[i] = rnd.next(99990, 100000);
            right[i] = rnd.next(99990, 100000);
        }
        for (int i = 0; i < n; ++i) {
            cross[i] = rnd.next(99990, 100000);
        }
    }

    println(n);
    println(cross);
    println(left);
    println(right);

    return 0;
}
