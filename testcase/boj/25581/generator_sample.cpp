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
        n = rnd.next(2, 4);
        int low = rnd.next(1, 20);
        int high = rnd.next(low, min(10000, low + 100));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(low, high));
    } else if (mode == 1) {
        n = rnd.next(5, 20);
        int value = rnd.next(1, 10000);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(6, 35);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(rnd.next(9000, 10000));
            } else {
                a.push_back(rnd.next(1, 50));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(6, 40);
        int x = rnd.next(1, 5000);
        int y = rnd.next(x, min(10000, x + rnd.next(0, 5000)));
        for (int i = 0; i < n; ++i) a.push_back((i % 2 == 0) ? x : y);
    } else if (mode == 4) {
        n = rnd.next(8, 60);
        int base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int value = base;
            for (int step = 0; step < rnd.next(0, 6); ++step) {
                value = min(10000, value * 2);
            }
            a.push_back(value);
        }
    } else if (mode == 5) {
        n = rnd.next(20, 90);
        int lo = rnd.next(1, 8000);
        int hi = rnd.next(lo, 10000);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else {
        n = rnd.next(2, 80);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 10000));
    }

    if (rnd.next(0, 1)) shuffle(a.begin(), a.end());
    if (rnd.next(0, 5) == 0) sort(a.begin(), a.end());
    if (rnd.next(0, 5) == 0) sort(a.rbegin(), a.rend());

    println(n);
    for (int value : a) println(value);

    return 0;
}
