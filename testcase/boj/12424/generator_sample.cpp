#include "testlib.h"
#include <array>
#include <vector>
using namespace std;

using ll = long long;

const ll MAX_N = 10000000000000LL;
const int MIN_P = -100000;
const int MAX_P = 100000;

array<ll, 3> partition(ll n, int mode) {
    if (mode == 0) {
        array<ll, 3> parts = {0, 0, 0};
        parts[rnd.next(0, 2)] = n;
        return parts;
    }

    if (mode == 1) {
        ll x = n / 3;
        ll y = n / 3;
        ll z = n - x - y;
        array<ll, 3> parts = {x, y, z};
        shuffle(parts.begin(), parts.end());
        return parts;
    }

    ll x = rnd.next(0LL, n);
    ll y = rnd.next(0LL, n - x);
    ll z = n - x - y;
    array<ll, 3> parts = {x, y, z};
    shuffle(parts.begin(), parts.end());
    return parts;
}

array<array<int, 3>, 3> payoffMatrix(int mode) {
    array<array<int, 3>, 3> p{};

    if (mode == 0) {
        return p;
    }

    if (mode == 1) {
        vector<int> values = {MIN_P, -1, 0, 1, MAX_P};
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                p[i][j] = rnd.any(values);
        return p;
    }

    if (mode == 2) {
        int base = rnd.next(-20, 20);
        int rowStep = rnd.next(-10, 10);
        int colStep = rnd.next(-10, 10);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                p[i][j] = base + rowStep * i + colStep * j;
        return p;
    }

    int lo = rnd.next(MIN_P, 0);
    int hi = rnd.next(0, MAX_P);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            p[i][j] = rnd.next(lo, hi);
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int sizeMode = rnd.next(0, 5);
        ll n;
        if (sizeMode == 0) {
            n = 1;
        } else if (sizeMode == 1) {
            n = rnd.next(2LL, 12LL);
        } else if (sizeMode == 2) {
            n = rnd.next(13LL, 1000LL);
        } else if (sizeMode == 3) {
            n = rnd.next(1000000LL, 1000000000LL);
        } else {
            n = MAX_N - rnd.next(0LL, 20LL);
        }

        int leftMode = rnd.next(0, 2);
        int rightMode = rnd.next(0, 2);
        array<ll, 3> left = partition(n, leftMode);
        array<ll, 3> right = partition(n, rightMode);

        println(n, left[0], left[1], left[2], right[0], right[1], right[2]);

        array<array<int, 3>, 3> p = payoffMatrix(rnd.next(0, 3));
        for (int i = 0; i < 3; ++i) {
            println(p[i][0], p[i][1], p[i][2]);
        }
    }

    return 0;
}
