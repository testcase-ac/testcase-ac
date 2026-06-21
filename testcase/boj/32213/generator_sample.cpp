#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomValue(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return 1 << rnd.next(0, 29);
    if (mode == 2) return (1 << rnd.next(1, 29)) - 1;
    if (mode == 3) return rnd.next(999999950, 1000000000);
    return rnd.next(1, 1000000000);
}

vector<int> makeCase(int mode) {
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else if (mode == 2) {
        n = rnd.next(3, 11);
    } else {
        n = rnd.next(12, 25);
    }

    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        a.push_back(randomValue(rnd.next(0, 5)));
        a.push_back(randomValue(rnd.next(0, 5)));
    } else if (mode == 1) {
        int base = randomValue(rnd.next(0, 3));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(randomValue(rnd.next(0, 3)));
            } else {
                a.push_back(base);
            }
        }
    } else if (mode == 2) {
        while ((int)a.size() + 3 <= n) {
            int x = 1;
            int y = 1;
            int z = 1;
            do {
                x = randomValue(rnd.next(0, 3));
                y = randomValue(rnd.next(0, 3));
                z = x ^ y;
            } while (z < 1 || z > 1000000000);
            a.push_back(x);
            a.push_back(y);
            a.push_back(z);
        }
        while ((int)a.size() < n) {
            a.push_back(randomValue(rnd.next(0, 4)));
        }
    } else {
        int valueMode = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) {
            a.push_back(randomValue(valueMode));
        }
    }

    shuffle(a.begin(), a.end());
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 12);
    vector<vector<int>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        cases.push_back(makeCase(rnd.next(0, 4)));
    }

    println(t);
    for (const vector<int>& a : cases) {
        println((int)a.size());
        println(a);
    }

    return 0;
}
