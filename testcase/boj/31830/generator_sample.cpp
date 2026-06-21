#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> randomRange(int n, int mode) {
    if (mode == 0) {
        int pos = rnd.next(1, n);
        return {pos, pos};
    }
    if (mode == 1) {
        int len = rnd.next(2, min(n, 4));
        int l = rnd.next(1, n - len + 1);
        return {l, l + len - 1};
    }
    if (mode == 2) {
        return {1, rnd.next(1, n)};
    }
    if (mode == 3) {
        return {rnd.next(1, n), n};
    }
    int l = rnd.next(1, n);
    int r = rnd.next(l, n);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 30);
    int q = rnd.next(3, 45);
    int alphabet = rnd.next(2, 26);
    int pattern = rnd.next(0, 4);

    string s;
    s.reserve(n);
    if (pattern == 0) {
        char c = char('A' + rnd.next(alphabet));
        s.assign(n, c);
    } else if (pattern == 1) {
        for (int i = 0; i < n; ++i) {
            s.push_back(char('A' + (i % alphabet)));
        }
    } else if (pattern == 2) {
        for (int i = 0; i < n; ++i) {
            s.push_back(char('A' + ((i / rnd.next(1, 4)) % alphabet)));
        }
    } else {
        while ((int)s.size() < n) {
            int run = rnd.next(1, min(6, n - (int)s.size()));
            char c = char('A' + rnd.next(alphabet));
            s.append(run, c);
        }
    }

    vector<int> types(q, 2);
    int firstQuery = rnd.next(q);
    types[firstQuery] = 1;
    for (int i = 0; i < q; ++i) {
        if (i != firstQuery && rnd.next(100) < 45) {
            types[i] = 1;
        }
    }

    println(n, q);
    println(s);
    for (int i = 0; i < q; ++i) {
        int mode = rnd.next(0, 4);
        auto [l, r] = randomRange(n, mode);
        println(types[i], l, r);
    }

    return 0;
}
