#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 30);
    if (mode == 5) {
        n = rnd.next(40, 120);
    }

    vector<int> a(n);
    if (mode == 0) {
        int value = rnd.next(1, n);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = min(n, i + 1 + rnd.next(0, 2));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = max(1, n - i - rnd.next(0, 2));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, min(n, 4));
        }
        for (int i = 0; i < n; i += rnd.next(3, 7)) {
            a[i] = rnd.next(max(1, n - 3), n);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, n);
        }
    }

    int q = rnd.next(1, min(60, 2 * n));
    if (mode == 5) {
        q = rnd.next(60, 140);
    }

    vector<int> interesting;
    interesting.push_back(1);
    interesting.push_back(n);
    for (int i = 0; i < n; ++i) {
        interesting.push_back(a[i]);
        interesting.push_back(min(n, a[i] + i));
        interesting.push_back(max(1, a[i] - 1));
        interesting.push_back(min(n, a[i] + 1));
    }

    vector<int> s(q);
    for (int i = 0; i < q; ++i) {
        if (rnd.next(0, 99) < 70) {
            s[i] = rnd.any(interesting);
        } else {
            s[i] = rnd.next(1, n);
        }
    }

    println(n);
    println(a);
    println(q);
    println(s);

    return 0;
}
