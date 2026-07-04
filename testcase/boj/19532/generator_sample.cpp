#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

static int boundedValue(int lo, int hi) {
    return rnd.next(lo, hi);
}

static pair<int, int> randomCoefficientPair(int x, int y) {
    for (int attempt = 0; attempt < 20000; ++attempt) {
        int a = rnd.next(-999, 999);
        int b = rnd.next(-999, 999);
        int c = a * x + b * y;
        if (-999 <= c && c <= 999) {
            return {a, b};
        }
    }

    if (rnd.next(2) == 0) {
        return {boundedValue(-1, 1), 0};
    }
    return {0, boundedValue(-1, 1)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> specialValues = {-999, -10, -2, -1, 0, 1, 2, 10, 999};
    int mode = rnd.next(5);
    int x;
    int y;

    if (mode == 0) {
        x = rnd.any(specialValues);
        y = rnd.any(specialValues);
    } else if (mode == 1) {
        x = rnd.next(-20, 20);
        y = rnd.next(-20, 20);
    } else if (mode == 2) {
        x = rnd.next(-999, 999);
        y = rnd.next(-2, 2);
    } else if (mode == 3) {
        x = rnd.next(-2, 2);
        y = rnd.next(-999, 999);
    } else {
        x = rnd.next(-999, 999);
        y = rnd.next(-999, 999);
    }

    int a, b, d, e;
    long long det;
    do {
        auto first = randomCoefficientPair(x, y);
        auto second = randomCoefficientPair(x, y);
        a = first.first;
        b = first.second;
        d = second.first;
        e = second.second;
        det = 1LL * a * e - 1LL * b * d;
    } while (det == 0);

    int c = a * x + b * y;
    int f = d * x + e * y;
    println(a, b, c, d, e, f);

    return 0;
}
