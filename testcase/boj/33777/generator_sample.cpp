#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string alternatingString(int n, char first) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back((i % 2 == 0) ? first : (first == 'O' ? 'E' : 'O'));
    }
    return s;
}

string runString(int n) {
    string s;
    s.reserve(n);
    char cur = rnd.any(string("OE"));
    while ((int)s.size() < n) {
        int remaining = n - (int)s.size();
        int len = rnd.next(1, remaining);
        s.append(len, cur);
        cur = (cur == 'O' ? 'E' : 'O');
    }
    return s;
}

string randomString(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.any(string("OE")));
    }
    return s;
}

string nearUniformString(int n) {
    char base = rnd.any(string("OE"));
    string s(n, base);
    int flips = rnd.next(1, n);
    for (int i = 0; i < flips; ++i) {
        int pos = rnd.next(0, n - 1);
        s[pos] = (base == 'O' ? 'E' : 'O');
    }
    return s;
}

string makeCase(int n, int mode) {
    if (mode == 0) return string(n, 'O');
    if (mode == 1) return string(n, 'E');
    if (mode == 2) return alternatingString(n, 'O');
    if (mode == 3) return alternatingString(n, 'E');
    if (mode == 4) return runString(n);
    if (mode == 5) return nearUniformString(n);
    return randomString(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    vector<pair<int, string>> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = 2;
        } else if (rnd.next(4) == 0) {
            n = rnd.next(15, 30);
        } else {
            n = rnd.next(3, 14);
        }

        int mode = (tc < 7) ? tc : rnd.next(0, 6);
        cases.push_back({n, makeCase(n, mode)});
    }

    println((int)cases.size());
    for (const auto& tc : cases) {
        println(tc.first);
        println(tc.second);
    }

    return 0;
}
