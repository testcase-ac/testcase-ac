#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeString(int n, int mode) {
    string s;
    if (mode == 0) {
        char c = char('A' + rnd.next(0, 2));
        s.assign(n, c);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) s += char('A' + (i % 2));
    } else if (mode == 2) {
        int alphabet = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) s += char('A' + rnd.next(0, alphabet - 1));
    } else if (mode == 3) {
        int alphabet = rnd.next(2, 4);
        s.assign(n, 'A');
        for (int i = 0; i < (n + 1) / 2; ++i) {
            char c = char('A' + rnd.next(0, alphabet - 1));
            s[i] = c;
            s[n - 1 - i] = c;
        }
    } else {
        int alphabet = rnd.next(2, 4);
        while ((int)s.size() < n) {
            char c = char('A' + rnd.next(0, alphabet - 1));
            int len = rnd.next(1, 5);
            s.append(min(len, n - (int)s.size()), c);
        }
    }

    if (rnd.next(0, 3) == 0) {
        int changes = rnd.next(1, max(1, n / 5));
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(0, n - 1);
            s[pos] = char('A' + rnd.next(0, 25));
        }
    }

    return s;
}

pair<int, int> makeQuery(int n, int mode) {
    if (mode == 0) return {1, n};
    if (mode == 1) {
        int l = rnd.next(1, n - 1);
        return {l, l + 1};
    }
    if (mode == 2) {
        if (n == 2) return {1, 2};
        int len = rnd.next(3, n);
        if (len % 2 == 0 && len < n) ++len;
        int l = rnd.next(1, n - len + 1);
        return {l, l + len - 1};
    }
    if (mode == 3) {
        int len = rnd.next(2, n);
        if (len % 2 == 1 && len < n) ++len;
        int l = rnd.next(1, n - len + 1);
        return {l, l + len - 1};
    }
    if (mode == 4) {
        int side = rnd.next(0, 1);
        int len = rnd.next(2, n);
        return side == 0 ? make_pair(1, len) : make_pair(n - len + 1, n);
    }

    int l = rnd.next(1, n - 1);
    int r = rnd.next(l + 1, n);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = rnd.next(2, 8);
    } else if (sizeMode == 1) {
        n = rnd.next(9, 20);
    } else if (sizeMode == 2) {
        n = rnd.next(21, 35);
    } else {
        n = rnd.next(36, 50);
    }

    string s = makeString(n, rnd.next(0, 4));

    int q = rnd.next(4, 20);
    if (rnd.next(0, 9) == 0) q = rnd.next(50, 100);

    vector<pair<int, int>> queries;
    queries.push_back({1, n});
    queries.push_back({1, 2});
    queries.push_back({n - 1, n});
    while ((int)queries.size() < q) {
        queries.push_back(makeQuery(n, rnd.next(0, 5)));
    }
    shuffle(queries.begin(), queries.end());

    println(n);
    println(s);
    println((int)queries.size());
    for (auto [l, r] : queries) println(l, r);

    return 0;
}
