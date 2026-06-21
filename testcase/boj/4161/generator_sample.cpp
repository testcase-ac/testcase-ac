#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

namespace {
const long long kLimit = 1000000000LL;

long long signedValue(long long value) {
    if (value == 0) {
        return 0;
    }
    return rnd.next(0, 1) ? value : -value;
}

pair<long long, long long> smallPoint() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return {rnd.next(-4, 4), rnd.next(-4, 4)};
    }
    if (mode == 1) {
        long long a = rnd.next(0, 25);
        long long b = rnd.next(0, 25);
        return {signedValue(a), signedValue(b)};
    }
    if (mode == 2) {
        long long a = rnd.next(0, 30);
        return {signedValue(a), signedValue(a)};
    }
    if (mode == 3) {
        long long a = rnd.next(0, 30);
        return {signedValue(a), signedValue(2 * a)};
    }
    return {signedValue(rnd.next(0, 35)), signedValue(rnd.next(20, 80))};
}

pair<long long, long long> largePoint() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return {signedValue(kLimit), signedValue(rnd.next(0LL, 40LL))};
    }
    if (mode == 1) {
        long long a = rnd.next(kLimit - 1000, kLimit);
        return {signedValue(a), signedValue(a)};
    }
    if (mode == 2) {
        long long x = rnd.next(kLimit / 2, kLimit);
        long long y = rnd.next(kLimit / 2, kLimit);
        return {signedValue(x), signedValue(y)};
    }
    if (mode == 3) {
        long long a = rnd.next(kLimit / 3, kLimit / 2);
        return {signedValue(a), signedValue(2 * a)};
    }
    return {signedValue(rnd.next(0LL, kLimit)), signedValue(rnd.next(0LL, kLimit))};
}
}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(4, 16);
    vector<pair<long long, long long>> points;
    points.push_back({0, 0});
    points.push_back({signedValue(1), signedValue(2)});

    while (static_cast<int>(points.size()) < cases) {
        if (rnd.next(0, 99) < 25) {
            points.push_back(largePoint());
        } else {
            points.push_back(smallPoint());
        }
    }

    shuffle(points.begin(), points.end());
    for (auto [x, y] : points) {
        println(x, y);
    }
    println("END");

    return 0;
}
