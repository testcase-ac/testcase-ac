#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<int> a(n);

    if (mode == 0) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 12);
            a[i] = min(cur, 100000);
        }
    } else if (mode == 1) {
        int cur = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            a[i] = cur;
            cur = max(1, cur - rnd.next(0, 3000));
        }
    } else if (mode == 2) {
        int kinds = rnd.next(1, min(6, n));
        vector<int> values;
        for (int i = 0; i < kinds; ++i) values.push_back(rnd.next(1, 40));
        sort(values.begin(), values.end());
        for (int i = 0; i < n; ++i) a[i] = rnd.any(values);
    } else if (mode == 3) {
        int low = rnd.next(1, 30);
        int high = rnd.next(low, min(100000, low + rnd.next(1, 100)));
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a[i] = rnd.next(low, high);
            } else {
                a[i] = rnd.next(1, low);
            }
        }
    } else if (mode == 4) {
        int block = rnd.next(2, 6);
        int base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int step = i / block;
            a[i] = min(100000, base + step * rnd.next(0, 15) + rnd.next(0, 3));
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else {
        int upper = rnd.any(vector<int>{10, 100, 1000, 100000});
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, upper);
    }

    println(n);
    for (int x : a) println(x);

    return 0;
}
