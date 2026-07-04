#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const int MAX_VALUE = 1000000000;
const long double LOG_LIMIT = 18.0L * logl(10.0L);

long double logSum(const vector<int>& values) {
    long double total = 0.0L;
    for (int value : values) {
        total += logl((long double)value);
    }
    return total;
}

int randomValue(int mode) {
    if (mode == 0) {
        return rnd.next(1, 20);
    }
    if (mode == 1) {
        return rnd.next(1, 1000);
    }
    if (mode == 2) {
        return rnd.next(900000000, MAX_VALUE);
    }

    static const vector<int> factors = {
        1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 16, 18, 20, 25, 27, 32,
        36, 40, 45, 50, 64, 72, 81, 100, 125, 128, 243, 256, 625,
        729, 1024, 3125, 59049, 1000000, MAX_VALUE
    };
    return rnd.any(factors);
}

void printCase(vector<int> a, vector<int> b) {
    shuffle(a.begin(), a.end());
    shuffle(b.begin(), b.end());

    println((int)a.size(), (int)b.size());
    println(a);
    println(b);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<int> a;
    vector<int> b;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        int m = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            a.push_back(randomValue(rnd.next(0, 1)));
        }
        for (int i = 0; i < m; ++i) {
            b.push_back(randomValue(rnd.next(0, 1)));
        }
    } else if (mode == 1) {
        int shared = rnd.next(1, 8);
        for (int i = 0; i < shared; ++i) {
            int value = randomValue(rnd.next(1, 3));
            a.push_back(value);
            b.push_back(value);
        }

        int extraA = rnd.next(1, 4);
        int extraB = rnd.next(1, 4);
        for (int i = 0; i < extraA; ++i) {
            a.push_back(randomValue(rnd.next(0, 1)));
        }
        for (int i = 0; i < extraB; ++i) {
            b.push_back(randomValue(rnd.next(0, 2)));
        }
    } else if (mode == 2) {
        int n = rnd.next(1, 5);
        int m = rnd.next(n, n + 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(randomValue(2));
        }
        for (int i = 0; i < m; ++i) {
            b.push_back(randomValue(rnd.next(1, 2)));
        }
    } else {
        int copies = rnd.next(1, 2);
        for (int i = 0; i < copies; ++i) {
            a.push_back(MAX_VALUE);
        }
        b.push_back(1);

        int smallExtras = rnd.next(0, 6);
        for (int i = 0; i < smallExtras; ++i) {
            if (rnd.next(0, 1) == 0) {
                a.push_back(rnd.next(1, 10));
            } else {
                b.push_back(rnd.next(1, 10));
            }
        }
    }

    while (logSum(a) - logSum(b) >= LOG_LIMIT - 1e-6L) {
        if (a.size() > 1 && rnd.next(0, 1) == 0) {
            a.pop_back();
        } else {
            b.push_back(randomValue(rnd.next(0, 1)));
        }
    }

    printCase(a, b);
    return 0;
}
