#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int h = 1;
    vector<int> d;

    if (mode == 0) {
        n = rnd.next(1, 3);
        int value = rnd.next(1, 5);
        d.assign(n, value);
        h = rnd.next(1, min(1000000, value * n + 2));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int maxValue = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            d.push_back(rnd.next(1, maxValue));
        }
        sort(d.begin(), d.end());

        int killAt = rnd.next(1, n);
        int before = accumulate(d.begin(), d.begin() + killAt - 1, 0);
        int through = before + d[killAt - 1];
        h = rnd.next(before + 1, through);
    } else if (mode == 2) {
        n = rnd.next(2, 15);
        int maxValue = rnd.next(1, 15);
        for (int i = 0; i < n; ++i) {
            d.push_back(rnd.next(1, maxValue));
        }
        sort(d.begin(), d.end());

        int total = accumulate(d.begin(), d.end(), 0);
        h = min(1000000, total + rnd.next(1, 20));
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        int value = rnd.next(1, 40);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                value += rnd.next(0, 3);
            }
            d.push_back(value);
        }

        int pivot = rnd.next(1, n);
        int prefix = accumulate(d.begin(), d.begin() + pivot, 0);
        h = rnd.next(max(1, prefix - d[pivot - 1] + 1), min(1000000, prefix));
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        int value = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            value += rnd.next(0, 20);
            d.push_back(value);
        }

        int total = accumulate(d.begin(), d.end(), 0);
        h = rnd.next(1, min(1000000, total));
    } else {
        n = rnd.next(1, 30);
        int maxValue = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            d.push_back(rnd.next(1, maxValue));
        }
        sort(d.begin(), d.end());
        h = rnd.next(1, 1000000);
    }

    println(n, h);
    println(d);

    return 0;
}
