#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<int> k;

    if (mode == 0) {
        k = {rnd.any(vector<int>{1, 2, 3, 10, 100, 100000})};
    } else if (mode == 1) {
        int n = rnd.next(2, 12);
        int value = rnd.any(vector<int>{1, 2, 3, rnd.next(4, 20)});
        k.assign(n, value);
    } else if (mode == 2) {
        int n = rnd.next(2, 18);
        k.assign(n, 1);
        int heavy = rnd.next(0, n - 1);
        k[heavy] = rnd.next(n, min(100000, n * rnd.next(2, 20)));
    } else if (mode == 3) {
        int n = rnd.next(3, 15);
        for (int i = 0; i < n; ++i) {
            k.push_back(i + 1 + rnd.next(0, 2));
        }
    } else if (mode == 4) {
        int n = rnd.next(4, 20);
        int a = 1;
        int b = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            k.push_back(min(1000, a));
            int c = min(1000, a + b + rnd.next(0, 1));
            a = b;
            b = c;
        }
    } else if (mode == 5) {
        int n = rnd.next(8, 40);
        int lo = rnd.next(1, 5);
        int hi = rnd.next(lo, 60);
        for (int i = 0; i < n; ++i) {
            k.push_back(rnd.next(lo, hi));
        }
    } else {
        int n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int valueMode = rnd.next(0, 4);
            if (valueMode == 0) {
                k.push_back(1);
            } else if (valueMode == 1) {
                k.push_back(rnd.next(2, 5));
            } else if (valueMode == 2) {
                k.push_back(rnd.next(6, 30));
            } else {
                k.push_back(rnd.next(31, 200));
            }
        }
    }

    shuffle(k.begin(), k.end());

    long long sum = accumulate(k.begin(), k.end(), 0LL);
    while (sum > 100000) {
        int i = rnd.next(0, (int)k.size() - 1);
        if (k[i] > 1) {
            --k[i];
            --sum;
        }
    }

    println((int)k.size());
    println(k);

    return 0;
}
