#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

using namespace std;

struct Value {
    int a;
    int b;
    int c;
    int d;
};

bool validReduced(int a, int b, int c) {
    return gcd(gcd(a, abs(b)), abs(c)) == 1;
}

Value makeValue(int d, int maxAbs, bool nonZero) {
    for (int attempt = 0; attempt < 10000; ++attempt) {
        int a = rnd.next(1, maxAbs);
        int b = rnd.next(-maxAbs, maxAbs);
        int c = d == 0 ? 0 : rnd.next(-maxAbs, maxAbs);
        if (d > 0 && c == 0) {
            continue;
        }
        if (nonZero && d == 0 && b == 0) {
            continue;
        }
        if (validReduced(a, b, c)) {
            return {a, b, c, d};
        }
    }

    if (d == 0) {
        return {1, nonZero ? 1 : 0, 0, 0};
    }
    return {1, 0, 1, d};
}

Value makeNearBoundaryValue(int d, bool nonZero) {
    vector<int> denominators = {1, 2, 3, 997, 999, 1000};
    vector<int> coefficients = {-1000, -999, -1, 0, 1, 999, 1000};

    for (int attempt = 0; attempt < 10000; ++attempt) {
        int a = rnd.any(denominators);
        int b = rnd.any(coefficients);
        int c = d == 0 ? 0 : rnd.any(coefficients);
        if (d > 0 && c == 0) {
            c = rnd.any(vector<int>{-1000, -999, -1, 1, 999, 1000});
        }
        if (nonZero && d == 0 && b == 0) {
            b = rnd.any(vector<int>{-1000, -999, -1, 1, 999, 1000});
        }
        if (validReduced(a, b, c)) {
            return {a, b, c, d};
        }
    }

    return makeValue(d, 1000, nonZero);
}

void printValue(const Value& value) {
    println(value.a, value.b, value.c, value.d);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> squareFreeD = {
        0, 2, 3, 5, 6, 7, 10, 11, 13, 17, 19, 23, 29, 30,
        31, 37, 41, 42, 43, 47, 53, 59, 61, 67, 70, 997
    };

    int mode = rnd.next(0, 5);
    int d = mode == 0 ? 0 : rnd.any(squareFreeD);
    if (mode != 0 && d == 0) {
        d = rnd.any(vector<int>{2, 3, 5, 6, 7, 10, 997});
    }

    Value a;
    Value b;
    if (mode == 0) {
        a = makeValue(0, rnd.next(1, 25), false);
        b = makeValue(0, rnd.next(1, 25), true);
    } else if (mode == 1) {
        int maxAbs = rnd.next(2, 20);
        a = makeValue(d, maxAbs, false);
        b = makeValue(d, maxAbs, true);
    } else if (mode == 2) {
        a = makeNearBoundaryValue(d, false);
        b = makeNearBoundaryValue(d, true);
    } else if (mode == 3) {
        int maxAbs = rnd.next(2, 60);
        a = makeValue(d, maxAbs, false);
        b = {a.a, -a.b, -a.c, d};
        if (!validReduced(b.a, b.b, b.c)) {
            b = makeValue(d, maxAbs, true);
        }
    } else if (mode == 4) {
        int maxAbs = rnd.next(2, 80);
        a = makeValue(d, maxAbs, false);
        b = {rnd.next(1, maxAbs), a.b, -a.c, d};
        if (!validReduced(b.a, b.b, b.c)) {
            b = makeValue(d, maxAbs, true);
        }
    } else {
        d = rnd.any(vector<int>{2, 3, 5, 6, 7, 10});
        a = {1, rnd.next(-5, 5), rnd.any(vector<int>{-3, -2, -1, 1, 2, 3}), d};
        b = {1, rnd.next(-5, 5), rnd.any(vector<int>{-3, -2, -1, 1, 2, 3}), d};
    }

    printValue(a);
    printValue(b);
    return 0;
}
