#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.any(string("ABC")));
    }
    return s;
}

string reducedLikeString(int targetLen) {
    string core;
    int coreLen = rnd.next(1, min(targetLen, 18));
    char last = 0;
    for (int i = 0; i < coreLen; ++i) {
        vector<char> choices = {'A', 'C'};
        if (last == 'A') choices = {'C'};
        if (last == 'C') choices = {'A'};
        char c = rnd.any(choices);
        core.push_back(c);
        last = c;
    }

    string s;
    int bParity = rnd.next(0, 1);
    for (char c : core) {
        if ((int)s.size() + 3 < targetLen && rnd.next(0, 2) == 0) {
            int repeat = 2 * rnd.next(1, 2);
            s.append(repeat, c);
        }
        s.push_back(c);
        if ((int)s.size() + 1 < targetLen && rnd.next(0, 2) == 0) {
            s.push_back('B');
            bParity ^= 1;
        }
    }
    while ((int)s.size() + 2 <= targetLen && rnd.next(0, 1) == 0) {
        s.insert(rnd.next(0, (int)s.size()), rnd.any(vector<string>{"AA", "BB", "CC"}));
    }
    if (bParity && (int)s.size() < targetLen) {
        s.push_back('B');
    }
    if (s.empty()) {
        s = rnd.any(string("ABC"));
    }
    if ((int)s.size() > targetLen) {
        s.resize(targetLen);
    }
    return s;
}

string applyInsertions(string s, int steps, int maxLen) {
    vector<string> pieces = {"AA", "BB", "CC", "ABAB", "BCBC"};
    for (int i = 0; i < steps; ++i) {
        string p = rnd.any(pieces);
        if ((int)s.size() + (int)p.size() > maxLen) {
            continue;
        }
        s.insert(rnd.next(0, (int)s.size()), p);
    }
    return s.empty() ? string(1, rnd.any(string("ABC"))) : s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 60);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        string u, v;

        if (mode == 0) {
            int len = rnd.next(1, 24);
            u = randomString(len);
            v = randomString(rnd.next(1, 24));
        } else if (mode == 1) {
            int len = rnd.next(1, 28);
            u = reducedLikeString(len);
            v = applyInsertions(u, rnd.next(1, 8), 60);
        } else if (mode == 2) {
            int len = rnd.next(1, 30);
            v = reducedLikeString(len);
            u = applyInsertions(v, rnd.next(1, 8), 60);
        } else if (mode == 3) {
            int len = rnd.next(70, 200);
            char a = rnd.any(string("ABC"));
            char b = rnd.any(string("ABC"));
            u.assign(len, a);
            v.assign(rnd.next(70, 200), b);
        } else if (mode == 4) {
            string base = rnd.any(vector<string>{"A", "B", "C", "AB", "BC", "AC", "ABC", "CBA"});
            u = applyInsertions(base, rnd.next(2, 20), 200);
            v = applyInsertions(base, rnd.next(2, 20), 200);
        } else {
            int len = rnd.next(1, 40);
            u = randomString(len);
            v = u;
            if (rnd.next(0, 1) == 0) {
                reverse(v.begin(), v.end());
            } else {
                v[rnd.next(0, (int)v.size() - 1)] = rnd.any(string("ABC"));
            }
        }

        println(u);
        println(v);
    }

    return 0;
}
