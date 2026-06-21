#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

string makeStack(int length, int k, int mode) {
    string s;
    s.reserve(length);

    if (mode == 0) {
        char c = static_cast<char>('0' + rnd.next(0, k - 1));
        return string(length, c);
    }

    if (mode == 1) {
        int start = rnd.next(0, k - 1);
        for (int i = 0; i < length; ++i) {
            s.push_back(static_cast<char>('0' + (start + i) % k));
        }
        return s;
    }

    if (mode == 2) {
        int a = rnd.next(0, k - 1);
        int b = rnd.next(0, k - 1);
        for (int i = 0; i < length; ++i) {
            s.push_back(static_cast<char>('0' + (i % 2 == 0 ? a : b)));
        }
        return s;
    }

    for (int i = 0; i < length; ++i) {
        s.push_back(static_cast<char>('0' + rnd.next(0, k - 1)));
    }
    return s;
}

pair<int, int> chooseLengths(int l, int mode) {
    if (l == 1) {
        return {1, 1};
    }

    if (mode == 0) {
        int n = rnd.next(1, l);
        return {n, n};
    }

    if (mode == 1) {
        int n = rnd.next(1, l - 1);
        int m = rnd.next(n + 1, l);
        return {n, m};
    }

    if (mode == 2) {
        int m = rnd.next(1, l - 1);
        int n = rnd.next(m + 1, l);
        return {n, m};
    }

    if (mode == 3) {
        return {1, l};
    }

    if (mode == 4) {
        return {l, 1};
    }

    return {rnd.next(1, l), rnd.next(1, l)};
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(1, 10);
    int l = rnd.next(1, 25);
    int g = rnd.next(1, 12);

    println(g);
    println(k, l);

    for (int game = 0; game < g; ++game) {
        int lengthMode = game < 6 ? game : rnd.next(0, 5);
        auto [n, m] = chooseLengths(l, lengthMode);

        int sMode = rnd.next(0, 3);
        int tMode = game % 4;
        if (rnd.next(0, 4) == 0) {
            tMode = sMode;
        }

        println(n);
        println(makeStack(n, k, sMode));
        println(m);
        println(makeStack(m, k, tMode));
    }

    return 0;
}
