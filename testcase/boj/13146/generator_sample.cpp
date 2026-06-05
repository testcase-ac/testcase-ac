#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(1, 1000000000));
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int value = rnd.next(1, 1000000000);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        int cur = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 10);
            a.push_back(cur);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        int cur = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            cur = max(1, cur - rnd.next(0, 10));
        }
    } else if (mode == 4) {
        n = rnd.next(3, 21);
        int low = rnd.next(1, 100);
        int high = rnd.next(low, low + 100);
        for (int i = 0; i < n; ++i) {
            a.push_back((i % 2 == 0) ? low : high);
        }
    } else if (mode == 5) {
        int groups = rnd.next(2, 8);
        int cur = rnd.next(1, 80);
        for (int g = 0; g < groups; ++g) {
            int len = rnd.next(1, 4);
            cur = max(1, cur + rnd.next(-15, 15));
            for (int i = 0; i < len; ++i) {
                a.push_back(cur);
            }
        }
        n = int(a.size());
    } else if (mode == 6) {
        n = rnd.next(4, 24);
        int peak = rnd.next(50, 200);
        int left = rnd.next(1, peak);
        int right = rnd.next(1, peak);
        for (int i = 0; i < n; ++i) {
            int dist = min(i, n - 1 - i);
            int value = peak - dist * rnd.next(0, 6);
            if (i < n / 2) value = max(left, value);
            else value = max(right, value);
            a.push_back(value);
        }
    } else if (mode == 7) {
        n = rnd.next(2, 18);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 9) == 0) {
                a.push_back(1000000000);
            } else {
                a.push_back(rnd.next(1, 1000));
            }
        }
    } else {
        n = rnd.next(3, 24);
        int alphabet = rnd.next(2, 6);
        vector<int> values;
        for (int i = 0; i < alphabet; ++i) {
            values.push_back(rnd.next(1, 200));
        }
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(values));
        }
    }

    println(n);
    for (int value : a) {
        println(value);
    }

    return 0;
}
