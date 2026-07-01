#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int smallNonzero(int limit) {
    int value = rnd.next(1, limit);
    return rnd.next(2) == 0 ? -value : value;
}

int maybeExtreme() {
    if (rnd.next(4) == 0) {
        return rnd.next(2) == 0 ? -1000000 : 1000000;
    }
    return smallNonzero(rnd.next(1, 1000));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 30);
    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(-rnd.next(1, 1000));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(4) == 0 ? 0 : rnd.next(1, 1000));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        a.push_back(-rnd.next(1, 1000));
        a.push_back(rnd.next(1, 1000));
        if (rnd.next(2) == 0) {
            a.push_back(0);
        }
        while ((int)a.size() < n) {
            a.push_back(maybeExtreme());
        }
    } else if (mode == 3) {
        n = rnd.next(4, 30);
        int first = smallNonzero(20);
        int second = smallNonzero(20);
        while (second == first) {
            second = smallNonzero(20);
        }
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(5);
            if (pick == 0) {
                a.push_back(0);
            } else if (pick <= 2) {
                a.push_back(first);
            } else {
                a.push_back(second);
            }
        }
    } else {
        n = rnd.next(2, 25);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(5) == 0) {
                a.push_back(rnd.next(2) == 0 ? -1000000 : 1000000);
            } else {
                a.push_back(rnd.next(-100, 100));
            }
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);
    return 0;
}
