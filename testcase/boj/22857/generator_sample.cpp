#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int evenValue() {
    return 2 * rnd.next(1, 500000);
}

int oddValue() {
    return 2 * rnd.next(0, 499999) + 1;
}

void appendRun(vector<int>& a, int len, bool even) {
    for (int i = 0; i < len; ++i) {
        a.push_back(even ? evenValue() : oddValue());
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = rnd.next(1, 100);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(1, 40);
        bool even = rnd.next(0, 1);
        appendRun(a, n, even);
    } else if (mode == 1) {
        int n = rnd.next(2, 80);
        bool startsEven = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            a.push_back(((i % 2 == 0) == startsEven) ? evenValue() : oddValue());
        }
    } else if (mode == 2) {
        int blocks = rnd.next(2, 8);
        for (int b = 0; b < blocks; ++b) {
            appendRun(a, rnd.next(1, 8), true);
            if (b + 1 < blocks) {
                appendRun(a, rnd.next(1, min(k + 2, 12)), false);
            }
        }
    } else if (mode == 3) {
        int blocks = rnd.next(3, 10);
        for (int b = 0; b < blocks; ++b) {
            appendRun(a, rnd.next(1, 10), rnd.next(0, 99) < 65);
        }
    } else {
        int n = rnd.next(20, 120);
        int evenPercent = rnd.next(10, 90);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 100) <= evenPercent ? evenValue() : oddValue());
        }
    }

    if (rnd.next(0, 4) == 0) {
        k = rnd.any(vector<int>{1, 2, 3, 99, 100});
    }

    println((int)a.size(), k);
    println(a);

    return 0;
}
