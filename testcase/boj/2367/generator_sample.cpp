#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

static vector<int> chooseDishes(int d, int z) {
    vector<int> dishes(d);
    iota(dishes.begin(), dishes.end(), 1);
    shuffle(dishes.begin(), dishes.end());
    dishes.resize(z);
    sort(dishes.begin(), dishes.end());
    return dishes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int k;
    int d;

    if (mode == 4) {
        n = rnd.next(25, 60);
        k = rnd.next(1, 5);
        d = rnd.next(12, 25);
    } else {
        n = rnd.next(3, 10);
        k = rnd.next(1, min(5, rnd.next(1, 4)));
        d = rnd.next(5, 12);
    }

    vector<int> limit(d);
    if (mode == 0) {
        for (int i = 0; i < d; ++i) {
            limit[i] = rnd.next(0, min(n, 3));
        }
    } else if (mode == 1) {
        for (int i = 0; i < d; ++i) {
            limit[i] = rnd.next(0, min(n, 2));
        }
        limit[rnd.next(d)] = 0;
    } else if (mode == 2) {
        for (int i = 0; i < d; ++i) {
            limit[i] = rnd.next(max(0, n - 2), n);
        }
    } else if (mode == 3) {
        for (int i = 0; i < d; ++i) {
            limit[i] = rnd.next(1, min(n, 5));
        }
    } else {
        for (int i = 0; i < d; ++i) {
            limit[i] = rnd.next(0, n);
        }
    }

    println(n, k, d);
    println(limit);

    for (int person = 0; person < n; ++person) {
        int z;
        if (mode == 0) {
            z = rnd.next(1, min(d, 3));
        } else if (mode == 1) {
            z = rnd.next(1, min(d, 4));
        } else if (mode == 2) {
            z = rnd.next(max(1, d - 3), d);
        } else if (mode == 3) {
            z = (person % 3 == 0) ? 1 : rnd.next(2, min(d, 6));
        } else {
            z = rnd.next(1, d);
        }

        vector<int> dishes = chooseDishes(d, z);
        cout << z;
        for (int dish : dishes) {
            cout << ' ' << dish;
        }
        cout << '\n';
    }

    return 0;
}
