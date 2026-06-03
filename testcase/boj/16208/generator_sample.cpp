#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(1, 101));
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        int value = rnd.next(1, 101);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo + 1, 101);
        for (int i = 0; i < n; ++i) {
            a.push_back(i % 2 == 0 ? lo : hi);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 101));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 40);
        int hiCount = rnd.next(1, n - 1);
        a.assign(n, 1);
        for (int i = 0; i < hiCount; ++i) {
            a[i] = 101;
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 5) {
        n = rnd.next(10, 80);
        int base = rnd.next(1, 101);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-3, 3);
            int value = base + delta;
            if (value < 1) value = 1;
            if (value > 101) value = 101;
            a.push_back(value);
        }
    } else if (mode == 6) {
        n = rnd.next(20, 120);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 101));
        }
    } else {
        n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            a.push_back(i + 1 <= 101 ? i + 1 : 101);
        }
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
