#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string toToken(long long value) {
    return to_string(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int degreeMode = rnd.next(0, 4);
    if (degreeMode == 0) {
        n = 1;
    } else if (degreeMode == 1) {
        n = rnd.next(2, 4);
    } else if (degreeMode == 2) {
        n = rnd.next(5, 8);
    } else {
        n = rnd.next(9, 10);
    }

    int rootMode = rnd.next(0, 3);
    int r;
    if (rootMode == 0) {
        r = rnd.next(1, 4);
    } else if (rootMode == 1) {
        r = rnd.next(5, 16);
    } else {
        r = rnd.next(17, 32);
    }

    int scale = rnd.next(1, 5);
    if (rnd.next(0, 1) == 1) {
        scale = -scale;
    }

    vector<long long> poly = {1};
    for (int i = 0; i < n - 1; ++i) {
        int b = rnd.next(1, 6);
        vector<long long> next(poly.size() + 1, 0);
        for (int j = 0; j < (int)poly.size(); ++j) {
            next[j] += poly[j];
            next[j + 1] += poly[j] * b;
        }
        poly = next;
    }

    vector<long long> coeffs(n + 1, 0);
    long long rootSquared = 1LL * r * r;
    for (int i = 0; i < (int)poly.size(); ++i) {
        coeffs[i] += scale * poly[i];
        coeffs[i + 1] -= scale * rootSquared * poly[i];
    }

    int kMode = rnd.next(0, 2);
    int k;
    if (kMode == 0) {
        k = 2;
    } else if (kMode == 1) {
        k = 2 * rnd.next(2, 20);
    } else {
        k = 2 * rnd.next(50, 1000);
    }

    println(n);
    vector<string> tokens;
    for (long long coefficient : coeffs) {
        tokens.push_back(toToken(coefficient));
    }
    println(tokens);
    println(k);

    return 0;
}
