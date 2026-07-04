#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomOdd(int lo, int hi) {
    int n = rnd.next(lo, hi);
    if (n % 2 == 0) {
        if (n == hi) --n;
        else ++n;
    }
    return n;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(12, 30);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;

        if (mode == 0) {
            vector<int> small = {3, 5, 7, 9, 11, 13, 15};
            n = rnd.any(small);
        } else if (mode == 1) {
            n = randomOdd(17, 99);
        } else if (mode == 2) {
            n = randomOdd(101, 9999);
        } else if (mode == 3) {
            n = randomOdd(999999001, 999999999);
        } else {
            n = randomOdd(3, 999999999);
        }

        int a;
        int b;
        int positionMode = rnd.next(0, 4);
        if (positionMode == 0) {
            a = rnd.any(vector<int>{1, n});
            b = rnd.next(1, n);
        } else if (positionMode == 1) {
            a = rnd.next(1, n);
            b = rnd.any(vector<int>{1, n});
        } else if (positionMode == 2) {
            int mid = (n + 1) / 2;
            int radius = min(5, n - 1);
            a = rnd.next(max(1, mid - radius), min(n, mid + radius));
            b = rnd.next(max(1, mid - radius), min(n, mid + radius));
        } else {
            a = rnd.next(1, n);
            b = rnd.next(1, n);
        }

        if (a == b) {
            if (b < n) ++b;
            else --b;
        }

        println(n, a, b);
    }

    return 0;
}
