#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const long long LIMIT = 100000000000LL;

long long reverseNumber(long long x) {
    string s = to_string(x);
    reverse(s.begin(), s.end());
    return stoll(s);
}

long long clampValue(long long x) {
    return min(max(x, 1LL), LIMIT);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long a, b;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a = rnd.next(1LL, 1000LL);
        b = rnd.next(a, min(LIMIT, a + rnd.next(0LL, 5000LL)));
    } else if (mode == 1) {
        a = rnd.next(1LL, LIMIT);
        b = rnd.next(a, min(LIMIT, a + rnd.next(0LL, 1000000LL)));
    } else if (mode == 2) {
        long long root = rnd.next(1LL, 316227LL);
        long long center = root * root;
        long long radius = rnd.next(0LL, 100000LL);
        a = clampValue(center - rnd.next(0LL, radius));
        b = clampValue(center + rnd.next(0LL, radius));
        if (a > b) swap(a, b);
    } else if (mode == 3) {
        long long root = rnd.next(1LL, 316227LL);
        long long square = root * root;
        while (square % 10 == 0) {
            root = rnd.next(1LL, 316227LL);
            square = root * root;
        }
        long long center = reverseNumber(square);
        long long radius = rnd.next(0LL, 100000LL);
        a = clampValue(center - rnd.next(0LL, radius));
        b = clampValue(center + rnd.next(0LL, radius));
        if (a > b) swap(a, b);
    } else if (mode == 4) {
        a = rnd.next(max(1LL, LIMIT - 1000000000LL), LIMIT);
        b = rnd.next(a, LIMIT);
    } else {
        vector<long long> anchors = {
            1LL, 9LL, 10LL, 99LL, 100LL, 999LL, 1000LL,
            9999LL, 10000LL, 999999LL, 1000000LL,
            9999999999LL, 10000000000LL, LIMIT
        };
        long long center = rnd.any(anchors);
        long long radius = rnd.next(0LL, 10000LL);
        a = clampValue(center - rnd.next(0LL, radius));
        b = clampValue(center + rnd.next(0LL, radius));
        if (a > b) swap(a, b);
    }

    println(a);
    println(b);
    return 0;
}
