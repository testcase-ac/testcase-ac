#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string randomBrackets(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.next(0, 1) == 0 ? '(' : ')');
    }
    return s;
}

string balancedBlocks(int n) {
    string s(n, '(');
    for (int i = n / 2; i < n; ++i) {
        s[i] = ')';
    }
    return s;
}

string alternatingBrackets(int n, bool startsOpen) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        bool open = (i % 2 == 0) == startsOpen;
        s.push_back(open ? '(' : ')');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 40);
    if (mode == 1 || mode == 2) {
        n += n % 2;
    }

    string s;
    if (mode == 0) {
        s = randomBrackets(n);
    } else if (mode == 1) {
        s = balancedBlocks(n);
    } else if (mode == 2) {
        s = alternatingBrackets(n, true);
    } else if (mode == 3) {
        s = alternatingBrackets(n, false);
    } else if (mode == 4) {
        s.assign(n, '(');
        int closeCount = rnd.next(1, n);
        for (int i = 0; i < closeCount; ++i) {
            s[n - 1 - i] = ')';
        }
    } else {
        s.assign(n, ')');
        int openCount = rnd.next(1, n);
        for (int i = 0; i < openCount; ++i) {
            s[i] = '(';
        }
    }

    vector<pair<int, int>> queries;
    queries.push_back({1, n});
    queries.push_back({rnd.next(1, n), rnd.next(1, n)});
    if (queries.back().first > queries.back().second) {
        swap(queries.back().first, queries.back().second);
    }

    int t = rnd.next(5, 30);
    while ((int)queries.size() < t) {
        int queryMode = rnd.next(0, 4);
        int l = 1;
        int r = n;

        if (queryMode == 0) {
            l = rnd.next(1, n);
            r = l;
        } else if (queryMode == 1) {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        } else if (queryMode == 2) {
            int len = rnd.next(1, min(n, 12));
            l = rnd.next(1, n - len + 1);
            r = l + len - 1;
        } else if (queryMode == 3) {
            int len = rnd.next(1, n / 2) * 2;
            l = rnd.next(1, n - len + 1);
            r = l + len - 1;
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
            if ((r - l + 1) % 2 == 0 && r < n) {
                ++r;
            }
        }

        queries.push_back({l, r});
    }

    println(n);
    println(s);
    println((int)queries.size());
    for (auto [l, r] : queries) {
        println(l, r);
    }

    return 0;
}
