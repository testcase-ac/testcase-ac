#include "testlib.h"
#include <cmath>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

long long digitCount(int a, int b) {
    if (a == 10) return 1LL * b + 1;
    if (a == 100) return 2LL * b + 1;
    if (a == 1000) return 3LL * b + 1;
    if (a == 10000) return 4LL * b + 1;
    return static_cast<long long>(floorl(log10l(a) * b)) + 1;
}

bool isAllowed(int a, int b) {
    string digits = to_string(digitCount(a, b));
    return digits.rfind("10000", 0) != 0 && digits.rfind("9999", 0) != 0;
}

pair<int, int> randomValidPair(int minA, int maxA, int minB, int maxB) {
    for (int attempt = 0; attempt < 10000; ++attempt) {
        int a = rnd.next(minA, maxA);
        int b = rnd.next(minB, maxB);
        if (isAllowed(a, b)) return {a, b};
    }
    quitf(_fail, "could not find a valid pair in range");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int a = 1;
    int b = 1;

    if (mode == 0) {
        a = 1;
        b = rnd.next(1, 10000000);
    } else if (mode == 1) {
        vector<int> powers = {10, 100, 1000, 10000};
        a = rnd.any(powers);
        b = rnd.next(1, 10000000);
        while (!isAllowed(a, b)) b = rnd.next(1, 10000000);
    } else if (mode == 2) {
        tie(a, b) = randomValidPair(2, 20, 1, 40);
    } else if (mode == 3) {
        tie(a, b) = randomValidPair(9000, 10000, 1, 200);
    } else if (mode == 4) {
        tie(a, b) = randomValidPair(2, 10000, 1000000, 10000000);
    } else if (mode == 5) {
        tie(a, b) = randomValidPair(2, 10000, 1, 10000000);
    } else {
        vector<pair<int, int>> anchors = {
            {2, 1}, {2, 10}, {3, 1000}, {9, 9999},
            {99, 101}, {999, 333}, {9999, 2}
        };
        tie(a, b) = rnd.any(anchors);
        while (!isAllowed(a, b)) tie(a, b) = rnd.any(anchors);
    }

    println(a, b);
    return 0;
}
