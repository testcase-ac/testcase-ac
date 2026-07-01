#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int MAX_A = 1000000000;

int onesInBase(int x, int base) {
    if (x == 0) return 0;
    int count = 0;
    while (x > 0) {
        if (x % base == 1) ++count;
        x /= base;
    }
    return count;
}

int valueWithBinaryOnes(int want) {
    vector<int> values;
    for (int x = 0; x <= 2047; ++x) {
        if (onesInBase(x, 2) == want) values.push_back(x);
    }
    if (!values.empty()) return rnd.any(values);
    return (1 << want) - 1;
}

int valueWithTernaryOnes(int want) {
    vector<int> values;
    for (int x = 0; x <= 59048; ++x) {
        if (onesInBase(x, 3) == want) values.push_back(x);
    }
    return rnd.any(values);
}

int nearExtreme() {
    vector<int> values = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        1023, 1024, 1025,
        59048, 59049, 59050,
        999999999, 1000000000
    };
    return rnd.any(values);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 20);
    vector<int> a;

    if (mode == 0) {
        int want = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(valueWithBinaryOnes(want));
        }
    } else if (mode == 1) {
        int want = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(valueWithTernaryOnes(want));
        }
    } else if (mode == 2) {
        int first = rnd.next(0, MAX_A);
        int second = rnd.next(0, MAX_A);
        for (int i = 0; i < n; ++i) {
            a.push_back(i % 2 == 0 ? first : second);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(nearExtreme());
            } else if (i % 3 == 1) {
                a.push_back(valueWithBinaryOnes(rnd.next(0, 10)));
            } else {
                a.push_back(valueWithTernaryOnes(rnd.next(0, 8)));
            }
        }
    } else if (mode == 4) {
        int limit = rnd.any(vector<int>{20, 100, 1000, 1000000, MAX_A});
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, limit));
        }
    } else {
        n = 20;
        for (int i = 0; i < n; ++i) {
            if (i < 10) {
                a.push_back((1 << i) - 1);
            } else {
                a.push_back(rnd.next(MAX_A - 100000, MAX_A));
            }
        }
    }

    shuffle(a.begin(), a.end());
    println(n);
    println(a);
    return 0;
}
