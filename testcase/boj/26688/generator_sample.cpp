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
        n = rnd.next(1, 12);
        a.assign(n, 1);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        a.reserve(n);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 8));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 25);
        a.reserve(n);
        int value = 1;
        for (int i = 0; i < n; ++i) {
            value = min(5000, value + rnd.next(0, max(1, value)));
            a.push_back(value);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 30);
        a.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(rnd.next(1000, 5000));
            } else {
                a.push_back(rnd.next(1, 20));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(10, 40);
        a.reserve(n);
        int base = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            a.push_back(min(5000, base + rnd.next(0, 3)));
        }
    } else if (mode == 5) {
        n = rnd.next(2, 60);
        a.reserve(n);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(4500, 5000));
        }
    } else {
        n = rnd.next(100, 5000);
        a.reserve(n);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 5000));
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);
    return 0;
}
