#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long smallValue() {
    return rnd.next(-30, 30);
}

long long positiveValue() {
    return rnd.next(1, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(-1000, -1));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        long long common = rnd.next(-5, 5);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(common);
            } else {
                a.push_back(smallValue());
            }
        }
    } else if (mode == 2) {
        n = rnd.any(vector<int>{3, 4, 8, 9, 15, 16, 24, 25});
        for (int i = 0; i < n; ++i) {
            if (i < rnd.next(1, n)) {
                a.push_back(positiveValue());
            } else {
                a.push_back(rnd.next(-1000, 0));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(5, 60);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 4);
            if (pick == 0) {
                a.push_back(-1000000000LL);
            } else if (pick == 1) {
                a.push_back(1000000000LL);
            } else {
                a.push_back(smallValue());
            }
        }
    } else if (mode == 4) {
        int side = rnd.next(2, 40);
        n = side * side + rnd.next(-1, 1);
        for (int i = 0; i < n; ++i) {
            long long value = (i % side == 0) ? positiveValue() : rnd.next(-100, 100);
            a.push_back(value);
        }
    } else {
        n = rnd.any(vector<int>{99999, 100000});
        for (int i = 0; i < n; ++i) {
            if (i < 400) {
                a.push_back(positiveValue());
            } else {
                a.push_back(rnd.next(-1000, 0));
            }
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    for (long long value : a) {
        println(value);
    }

    return 0;
}
