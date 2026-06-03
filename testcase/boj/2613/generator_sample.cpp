#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        m = 1;
        int hi = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, hi));
    } else if (mode == 1) {
        n = rnd.next(1, 18);
        m = n;
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 100));
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        m = rnd.next(1, n);
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int value = base + rnd.next(0, 4);
            a.push_back(min(value, 100));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 32);
        m = rnd.next(2, n);
        for (int i = 0; i < n; ++i) {
            if (i % rnd.next(2, 5) == 0) {
                a.push_back(rnd.next(70, 100));
            } else {
                a.push_back(rnd.next(1, 12));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(3, 28);
        m = rnd.next(2, n);
        int low = rnd.next(1, 15);
        int high = rnd.next(60, 100);
        for (int i = 0; i < n; ++i) {
            a.push_back((i % 2 == 0) ? high : low + rnd.next(0, 10));
        }
    } else {
        m = rnd.next(2, 10);
        vector<int> groupSizes;
        n = 0;
        for (int i = 0; i < m; ++i) {
            int len = rnd.next(1, 5);
            groupSizes.push_back(len);
            n += len;
        }

        for (int len : groupSizes) {
            int sum = 0;
            for (int i = 0; i < len; ++i) {
                int remaining = len - i;
                int value = rnd.next(1, min(100, 20 + sum / remaining + 5));
                a.push_back(value);
                sum += value;
            }
        }
    }

    println(n, m);
    println(a);
    return 0;
}
