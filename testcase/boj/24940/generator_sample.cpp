#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int smallValue() {
    int x = rnd.next(1, 20);
    if (rnd.next(10) == 0) x = rnd.next(100000, 1000000);
    return x;
}

int signedValue(int sign) {
    return sign * smallValue();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 20);
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 15);
        int sign = rnd.next(2) == 0 ? -1 : 1;
        for (int i = 0; i < n; ++i) {
            a.push_back(signedValue(sign));
        }
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int roll = rnd.next(10);
            if (roll < 5) {
                a.push_back(0);
            } else {
                int sign = rnd.next(2) == 0 ? -1 : 1;
                a.push_back(signedValue(sign));
            }
        }
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        int sign = rnd.next(2) == 0 ? -1 : 1;
        for (int i = 0; i < n; ++i) {
            a.push_back(signedValue((i % 2 == 0) ? sign : -sign));
        }
    } else if (mode == 3) {
        int pairs = rnd.next(1, 8);
        n = pairs * 2 + rnd.next(0, 2);
        for (int i = 0; i < pairs; ++i) {
            int x = smallValue();
            if (rnd.next(2) == 0) {
                a.push_back(x);
                a.push_back(-x);
            } else {
                a.push_back(-x);
                a.push_back(x);
            }
        }
        while ((int)a.size() < n) {
            a.push_back(rnd.next(2) == 0 ? 0 : signedValue(rnd.next(2) == 0 ? -1 : 1));
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(4, 20);
        int sign = rnd.next(2) == 0 ? -1 : 1;
        while ((int)a.size() < n) {
            int run = rnd.next(1, min(5, n - (int)a.size()));
            for (int i = 0; i < run; ++i) {
                a.push_back(signedValue(sign));
            }
            sign *= -1;
        }
    } else {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int sign = rnd.next(2) == 0 ? -1 : 1;
            int x = rnd.next(3) == 0 ? rnd.next(900000, 1000000) : rnd.next(0, 30);
            a.push_back(sign * x);
        }
    }

    println((int)a.size());
    println(a);

    return 0;
}
