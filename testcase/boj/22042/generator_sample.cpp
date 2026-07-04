#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 99));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        vector<int> pool = {1, 2, 3, 4, 5, 10, 20, 25, 33, 40, 50, 75, 90, 99};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(rnd.next(1, 99));
            } else {
                a.push_back(rnd.next(100, 500));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(1000000000);
            } else {
                a.push_back(rnd.next(999999900, 1000000000));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(base * rnd.next(1, 5));
        }
    } else {
        n = rnd.next(3, 12);
        int remaining = rnd.next(60, 140);
        for (int i = 0; i < n; ++i) {
            int value;
            if (i + 1 == n) {
                value = max(1, remaining);
            } else {
                value = rnd.next(1, max(1, remaining / 2));
                remaining -= value;
            }
            a.push_back(value);
        }
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
