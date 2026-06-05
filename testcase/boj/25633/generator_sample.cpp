#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 12));
        }
    } else if (mode == 1) {
        n = rnd.next(5, 35);
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(10, 200)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
        sort(a.begin(), a.end());
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 2) {
        n = rnd.next(6, 45);
        long long sum = rnd.next(1, 20);
        a.push_back((int)sum);
        for (int i = 1; i < n; ++i) {
            int value;
            if (rnd.next(0, 3) == 0) {
                value = rnd.next((int)min<long long>(1000000, sum + 1), 1000000);
            } else {
                value = rnd.next(1, (int)min<long long>(1000000, sum));
            }
            a.push_back(value);
            sum = min<long long>(1000000, sum + value);
        }
    } else if (mode == 3) {
        n = rnd.next(10, 70);
        int blocks = rnd.next(2, 7);
        for (int b = 0; b < blocks && (int)a.size() < n; ++b) {
            int base = rnd.next(1, 500);
            int len = rnd.next(1, max(1, n / blocks + 4));
            for (int i = 0; i < len && (int)a.size() < n; ++i) {
                a.push_back(min(1000000, base + rnd.next(0, 25)));
            }
        }
        while ((int)a.size() < n) {
            a.push_back(rnd.next(1, 500));
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(8, 60);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                a.push_back(rnd.next(900000, 1000000));
            } else {
                a.push_back(rnd.next(1, 1000));
            }
        }
    } else {
        n = rnd.next(80, 150);
        int value = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            value = min(1000000, value + rnd.next(0, 50));
            a.push_back(value);
        }
        for (int i = 0; i < n / 5; ++i) {
            swap(a[rnd.next(n)], a[rnd.next(n)]);
        }
    }

    println((int)a.size());
    println(a);

    return 0;
}
