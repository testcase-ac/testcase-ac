#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long withSign(long long x) {
    return rnd.next(0, 1) ? x : -x;
}

long long nonZero(long long lo, long long hi) {
    long long x = 0;
    while (x == 0) {
        x = rnd.next(lo, hi);
    }
    return x;
}

pair<long long, long long> fibonacciLike() {
    vector<long long> values = {1, 1};
    int terms = rnd.next(4, 12);
    for (int i = 2; i < terms; ++i) {
        values.push_back(values[i - 1] + values[i - 2]);
    }

    long long scale = rnd.next(1, 1000000);
    long long a = values[terms - 1] * scale;
    long long b = values[terms - 2] * scale;
    if (rnd.next(0, 1)) {
        swap(a, b);
    }
    return {withSign(a), withSign(b)};
}

pair<long long, long long> nearLimitPair() {
    long long a = LIMIT - rnd.next(0LL, 1000000LL);
    long long b = rnd.next(1LL, 1000000LL);

    int shape = rnd.next(0, 2);
    if (shape == 1) {
        b = LIMIT - rnd.next(0LL, 1000000LL);
    } else if (shape == 2) {
        a = (LIMIT / b) * b;
    }

    return {withSign(a), withSign(b)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    pair<long long, long long> input;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        input = {0, rnd.next(-1000000LL, 1000000LL)};
    } else if (mode == 1) {
        long long base = nonZero(-1000000LL, 1000000LL);
        long long mul = nonZero(-1000000LL, 1000000LL);
        input = {base, base * mul};
    } else if (mode == 2) {
        input = fibonacciLike();
    } else if (mode == 3) {
        input = {
            nonZero(-1000000000LL, 1000000000LL),
            nonZero(-1000000000LL, 1000000000LL),
        };
    } else if (mode == 4) {
        input = nearLimitPair();
    } else if (mode == 5) {
        long long a = rnd.next(-1000000LL, 1000000LL);
        long long b = rnd.next(-1000000LL, 1000000LL);
        input = {a, b};
    } else {
        long long a = nonZero(1LL, 1000000000LL);
        long long b = nonZero(1LL, 1000000000LL);
        input = {a, -b};
    }

    println(input.first, input.second);
    return 0;
}
