#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> makePassengers(int n, int mode) {
    vector<int> p(n);

    if (mode == 0) {
        for (int& x : p) {
            x = rnd.next(0, 100);
        }
    } else if (mode == 1) {
        for (int& x : p) {
            x = rnd.next(0, 3) == 0 ? rnd.next(1, 100) : 0;
        }
    } else if (mode == 2) {
        vector<int> boundary = {0, 1, 8, 9, 10, 11, 18, 19, 20, 21,
                                28, 29, 30, 31, 98, 99, 100};
        for (int& x : p) {
            x = rnd.any(boundary);
        }
    } else if (mode == 3) {
        int base = rnd.next(0, 10) * 10;
        for (int i = 0; i < n; ++i) {
            p[i] = (i % 2 == 0) ? base : rnd.next(0, 100);
        }
    } else {
        for (int& x : p) {
            x = rnd.next(0, 1) ? rnd.next(90, 100) : rnd.next(0, 10);
        }
    }

    return p;
}

static vector<int> makeOrder(int n, int mode) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);

    if (mode == 0) {
        shuffle(order.begin(), order.end());
    } else if (mode == 1) {
        if (rnd.next(0, 1)) {
            reverse(order.begin(), order.end());
        }
    } else if (mode == 2) {
        order.clear();
        int left = 1, right = n;
        while (left <= right) {
            if (rnd.next(0, 1)) {
                order.push_back(left++);
            } else {
                order.push_back(right--);
            }
        }
    } else if (mode == 3) {
        order.clear();
        int center = rnd.next(1, n);
        for (int d = 0; d < n; ++d) {
            int a = center - d;
            int b = center + d;
            if (a >= 1) {
                order.push_back(a);
            }
            if (b <= n && b != a) {
                order.push_back(b);
            }
        }
    } else {
        vector<int> odds, evens;
        for (int i = 1; i <= n; ++i) {
            (i % 2 ? odds : evens).push_back(i);
        }
        shuffle(odds.begin(), odds.end());
        shuffle(evens.begin(), evens.end());
        order = odds;
        order.insert(order.end(), evens.begin(), evens.end());
    }

    return order;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n;
    if (sizeMode < 2) {
        n = 3;
    } else if (sizeMode < 7) {
        n = rnd.next(4, 20);
    } else {
        n = rnd.next(21, 80);
    }

    vector<int> passengers = makePassengers(n, rnd.next(0, 4));
    vector<int> order = makeOrder(n, rnd.next(0, 4));

    println(n);
    println(passengers);
    println(order);

    return 0;
}
