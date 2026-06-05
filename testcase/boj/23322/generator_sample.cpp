#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(30, 120);
    } else {
        n = rnd.next(2, 20);
    }

    int k;
    if (rnd.next(0, 3) == 0) {
        k = rnd.next(1, min(n - 1, 3));
    } else if (rnd.next(0, 4) == 0) {
        k = n - 1;
    } else {
        k = rnd.next(1, n - 1);
    }

    vector<int> a(n);
    if (mode == 0) {
        fill(a.begin(), a.end(), rnd.next(1, 2000));
    } else if (mode == 1) {
        int low = rnd.next(1, 1999);
        int high = rnd.next(low + 1, 2000);
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) {
            a[i] = (i < split ? low : high);
        }
    } else if (mode == 2) {
        int groups = rnd.next(2, min(n, 6));
        vector<int> values;
        int cur = rnd.next(1, 12);
        for (int i = 0; i < groups; ++i) {
            cur += rnd.next(0, 7);
            values.push_back(min(cur, 2000));
        }
        for (int i = 0; i < n; ++i) {
            a[i] = values[rnd.next(0, groups - 1)];
        }
        sort(a.begin(), a.end());
    } else if (mode == 3) {
        int start = rnd.next(1, 50);
        int step = rnd.next(0, 15);
        for (int i = 0; i < n; ++i) {
            a[i] = min(2000, start + step * i + rnd.next(0, 2));
        }
        sort(a.begin(), a.end());
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) {
                a[i] = rnd.next(1, 5);
            } else if (bucket == 1) {
                a[i] = rnd.next(6, 50);
            } else if (bucket == 2) {
                a[i] = rnd.next(51, 500);
            } else if (bucket == 3) {
                a[i] = rnd.next(501, 1500);
            } else {
                a[i] = rnd.next(1501, 2000);
            }
        }
        sort(a.begin(), a.end());
    } else {
        int value = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            value += rnd.next(0, 4);
            a[i] = min(value, 2000);
        }
    }

    println(n, k);
    println(a);

    return 0;
}
