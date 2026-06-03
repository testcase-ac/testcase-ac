#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomMixed(int n) {
    string s;
    s.reserve(n);

    string alphabet = "01?";
    for (int i = 0; i < n; ++i) s += rnd.any(alphabet);

    return s;
}

string alternating(int n) {
    string s;
    s.reserve(n);

    vector<char> chars = {'0', '1', '?'};
    shuffle(chars.begin(), chars.end());
    for (int i = 0; i < n; ++i) s += chars[i % (int)chars.size()];

    return s;
}

string blocky(int n) {
    string s;
    s.reserve(n);

    string alphabet = "01?";
    while ((int)s.size() < n) {
        char c = rnd.any(alphabet);
        int len = rnd.next(1, min(6, n - (int)s.size()));
        s.append(len, c);
    }

    return s;
}

string sparseUnknowns(int n) {
    string s(n, rnd.next(0, 1) ? '0' : '1');
    int flips = rnd.next(1, n);
    for (int i = 0; i < flips; ++i) s[rnd.next(n)] = '?';
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc < 3) {
            n = 1;
        } else if (rnd.next(100) < 80) {
            n = rnd.next(2, 30);
        } else {
            n = rnd.next(31, 80);
        }

        string b;
        int mode = tc < 3 ? tc : rnd.next(8);
        if (mode == 0) {
            b.assign(n, '0');
        } else if (mode == 1) {
            b.assign(n, '1');
        } else if (mode == 2) {
            b.assign(n, '?');
        } else if (mode == 3) {
            b = randomMixed(n);
            b[0] = '0';
        } else if (mode == 4) {
            b = randomMixed(n);
            b[n - 1] = '1';
        } else if (mode == 5) {
            b = alternating(n);
        } else if (mode == 6) {
            b = blocky(n);
        } else {
            b = sparseUnknowns(n);
        }

        println(n, b);
    }

    return 0;
}
