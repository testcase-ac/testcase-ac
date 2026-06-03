#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 25);
    vector<int> t(n);

    if (mode == 0) {
        for (int& x : t) x = rnd.next(1, 100);
    } else if (mode == 1) {
        n = rnd.next(8, 35);
        t.assign(n, 30);
        int tweaks = rnd.next(1, n);
        for (int i = 0; i < tweaks; ++i) {
            t[rnd.next(0, n - 1)] = rnd.any(vector<int>{1, 14, 15, 16, 29, 31, 59, 60, 61, 100});
        }
    } else if (mode == 2) {
        n = rnd.next(6, 30);
        t.resize(n);
        vector<int> boundary = {14, 15, 16, 29, 30, 31, 44, 45, 46, 59, 60, 61};
        for (int& x : t) x = rnd.any(boundary);
    } else if (mode == 3) {
        n = rnd.next(10, 40);
        t.resize(n);
        int low = rnd.next(1, 10);
        int high = rnd.next(55, 100);
        for (int i = 0; i < n; ++i) t[i] = (i % 2 == 0) ? low : high;
        if (rnd.next(0, 1)) reverse(t.begin(), t.end());
    } else if (mode == 4) {
        n = rnd.next(12, 45);
        t.resize(n);
        int chunk = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) {
            if ((i / chunk) % 2 == 0) {
                t[i] = rnd.next(1, 20);
            } else {
                t[i] = rnd.next(40, 100);
            }
        }
    } else if (mode == 5) {
        n = 100;
        t.resize(n);
        int value = rnd.any(vector<int>{1, 15, 30, 31, 60, 100});
        fill(t.begin(), t.end(), value);
        int tweaks = rnd.next(0, 20);
        for (int i = 0; i < tweaks; ++i) t[rnd.next(0, n - 1)] = rnd.next(1, 100);
    } else {
        n = rnd.next(1, 5);
        t.resize(n);
        for (int& x : t) x = rnd.any(vector<int>{1, 2, 29, 30, 31, 99, 100});
    }

    println(n);
    for (int x : t) println(x);
    return 0;
}
