#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string repeatedPattern(int n, const string& pattern) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(pattern[i % (int)pattern.size()]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 2 * rnd.next(1, 25);
    int q = rnd.next(1, 80);

    string s;
    if (mode == 0) {
        s = repeatedPattern(n, "()");
    } else if (mode == 1) {
        s = string(n / 2, '(') + string(n / 2, ')');
    } else if (mode == 2) {
        s = repeatedPattern(n, ")(");
    } else if (mode == 3) {
        s.assign(n, '(');
        int closeCount = rnd.next(0, n);
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) {
            positions[i] = i;
        }
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < closeCount; ++i) {
            s[positions[i]] = ')';
        }
    } else if (mode == 4) {
        s = repeatedPattern(n, rnd.next(0, 1) ? "(()" : "())");
    } else {
        s.resize(n);
        for (char& c : s) {
            c = rnd.next(0, 1) ? '(' : ')';
        }
    }

    println(n);
    println(s);
    println(q);

    for (int i = 0; i < q; ++i) {
        bool forceAnswerQuery = (i == q - 1);
        int type = forceAnswerQuery ? 2 : rnd.next(1, 2);
        if (type == 1) {
            println(1, rnd.next(1, n));
            continue;
        }

        int l = rnd.next(1, n);
        int r;
        int rangeMode = rnd.next(0, 3);
        if (rangeMode == 0) {
            r = l;
        } else if (rangeMode == 1) {
            r = min(n, l + rnd.next(0, 5));
        } else if (rangeMode == 2) {
            r = rnd.next(l, n);
        } else {
            l = 1;
            r = n;
        }
        println(2, l, r);
    }

    return 0;
}
