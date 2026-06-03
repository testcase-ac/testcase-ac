#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        vector<int> interesting = {1, 2, 1439, 1440, 1441, 2000};
        a.push_back(rnd.any(interesting));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int big = rnd.next(1, 2000);
        a.push_back(big);
        for (int i = 1; i < n; ++i) {
            int cap = max(1, min(2000, big / max(1, n - 1) + rnd.next(0, 8)));
            a.push_back(rnd.next(1, cap));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        int lo = rnd.next(1, 40);
        int hi = rnd.next(lo, min(2000, lo + rnd.next(0, 120)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        int target = rnd.next(1420, 1465);
        int remaining = target;
        for (int i = 0; i < n; ++i) {
            int left = n - i - 1;
            int x = rnd.next(1, max(1, min(2000, remaining - left)));
            a.push_back(x);
            remaining -= x;
        }
        a.back() += remaining;
    } else if (mode == 4) {
        n = rnd.next(2, 14);
        int half = rnd.next(650, 1500);
        a.push_back(half);
        a.push_back(half + rnd.next(-3, 3));
        for (int i = 2; i < n; ++i) a.push_back(rnd.next(1, 20));
    } else if (mode == 5) {
        n = rnd.next(40, 100);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 30));
    } else {
        n = rnd.next(2, 25);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                a.push_back(rnd.next(1400, 2000));
            } else {
                a.push_back(rnd.next(1, 80));
            }
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
