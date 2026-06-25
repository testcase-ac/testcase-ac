#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(1, 1000000000));
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 8);
        for (int i = 0; i < n / 2; ++i) {
            int x = rnd.next(1, 1000000000);
            a.push_back(x);
            a.push_back(x);
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(2, 16);
        int xr = 1;
        for (int i = 0; i + 1 < n; ++i) {
            int x = rnd.next(1, 1000000);
            a.push_back(x);
            xr ^= x;
        }
        if (xr == 0) {
            a[0] ^= 2;
            xr ^= 2;
        }
        a.push_back(xr);
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        int xr = 0;
        for (int i = 0; i + 1 < n; ++i) {
            int x = rnd.next(1, 1000000);
            a.push_back(x);
            xr ^= x;
        }
        int target = rnd.next(2, 1023);
        a.push_back(xr ^ target);
        if (a.back() == 0) a.back() = target;
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            int bit = rnd.next(0, 29);
            int delta = rnd.next(0, 3);
            int x = (1 << bit) + delta;
            a.push_back(min(x, 1000000000));
        }
    } else {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(1000000000 - rnd.next(0, 20));
            } else {
                a.push_back(rnd.next(1, 1000000000));
            }
        }
    }

    println((int)a.size());
    for (int x : a) {
        println(x);
    }

    return 0;
}
