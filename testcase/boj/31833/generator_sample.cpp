#include "testlib.h"

#include <vector>

using namespace std;

static vector<int> randomArray(int n) {
    vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(4) == 0) {
            values.push_back(rnd.next(1, 9));
        } else {
            values.push_back(rnd.next(1, 99));
        }
    }
    return values;
}

static vector<int> patternArray(int n, int mode) {
    vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            values.push_back(rnd.next(1, 9));
        } else if (mode == 1) {
            values.push_back(rnd.next(10, 99));
        } else if (mode == 2) {
            values.push_back(i % 2 == 0 ? rnd.next(1, 9) : rnd.next(10, 99));
        } else {
            int base = rnd.any(vector<int>{1, 9, 10, 11, 19, 90, 99});
            values.push_back(max(1, min(99, base + rnd.next(-1, 1))));
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = mode == 4 ? 9 : rnd.next(1, 9);

    vector<int> a;
    vector<int> b;

    if (mode == 0) {
        a = randomArray(n);
        b = a;
    } else if (mode == 1) {
        a = patternArray(n, 0);
        b = patternArray(n, 1);
    } else if (mode == 2) {
        a = patternArray(n, 2);
        b = patternArray(n, 2);
        if (n >= 2) {
            a[0] = rnd.next(1, 9);
            b[0] = a[0] * 10 + rnd.next(0, 9);
        }
    } else if (mode == 3) {
        a = patternArray(n, 3);
        b = patternArray(n, 3);
    } else {
        a.assign(n, rnd.any(vector<int>{9, 99}));
        b = randomArray(n);
        if (rnd.next(2) == 0) {
            b.assign(n, 99);
        }
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
