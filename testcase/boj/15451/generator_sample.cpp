#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        int value = rnd.next(-20, 20);
        a.assign(n, value);
    } else if (mode == 1) {
        int center = rnd.next(-50, 50);
        int radius = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(center + rnd.next(-radius, radius));
        }
    } else if (mode == 2) {
        int leftCount = rnd.next(1, n);
        int left = rnd.next(-1000000000, -999999980);
        int right = rnd.next(999999980, 1000000000);
        for (int i = 0; i < leftCount; ++i) {
            a.push_back(left + rnd.next(0, 5));
        }
        while ((int)a.size() < n) {
            a.push_back(right - rnd.next(0, 5));
        }
    } else if (mode == 3) {
        int start = rnd.next(-100, 100);
        int step = rnd.next(0, 12);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + i * step);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int sign = rnd.next(0, 1) == 0 ? -1 : 1;
            a.push_back(sign * rnd.next(0, 200));
        }
    } else {
        vector<int> pool = {-1000000000, -7, -1, 0, 1, 7, 1000000000};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    }

    shuffle(a.begin(), a.end());

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = n;
    } else if (kMode == 2) {
        k = (n + 1) / 2;
    } else {
        k = rnd.next(1, n);
    }

    println(n, k);
    println(a);

    return 0;
}
