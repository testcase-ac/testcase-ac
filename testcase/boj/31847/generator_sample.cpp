#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string makeString(int n, int mode) {
    string s;
    s.reserve(n);

    if (mode == 0) {
        char c = char('A' + rnd.next(0, 3));
        s.assign(n, c);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            s.push_back(char('A' + (i % rnd.next(2, 4))));
        }
    } else if (mode == 2) {
        string base = "ABBA";
        for (int i = 0; i < n; ++i) {
            s.push_back(base[i % (int)base.size()]);
        }
    } else if (mode == 3) {
        int alphabet = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            s.push_back(char('A' + rnd.next(0, alphabet - 1)));
        }
    } else {
        int half = (n + 1) / 2;
        string left;
        for (int i = 0; i < half; ++i) {
            left.push_back(char('A' + rnd.next(0, 3)));
        }
        s = left;
        for (int i = n - half - 1; i >= 0; --i) {
            s.push_back(left[i]);
        }
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 30);
    int q = rnd.next(1, 50);
    string s = makeString(n, rnd.next(0, 4));

    vector<pair<int, int>> queries;
    queries.push_back({1, n});
    if (n > 2) {
        queries.push_back({1, rnd.next(2, n)});
        queries.push_back({rnd.next(1, n - 1), n});
    }

    while ((int)queries.size() < q) {
        int mode = rnd.next(0, 4);
        int l, r;
        if (mode == 0) {
            l = rnd.next(1, n - 1);
            r = l + 1;
        } else if (mode == 1) {
            int len = rnd.next(2, min(n, 6));
            l = rnd.next(1, n - len + 1);
            r = l + len - 1;
        } else if (mode == 2) {
            int len = rnd.next(2, n);
            if (len % 2 == 1 && len < n) {
                ++len;
            }
            l = rnd.next(1, n - len + 1);
            r = l + len - 1;
        } else if (mode == 3) {
            int len = rnd.next(2, n);
            if (len % 2 == 0 && len < n) {
                ++len;
            }
            l = rnd.next(1, n - len + 1);
            r = l + len - 1;
        } else {
            l = rnd.next(1, n - 1);
            r = rnd.next(l + 1, n);
        }
        queries.push_back({l, r});
    }

    shuffle(queries.begin(), queries.end());

    println(n);
    println(s);
    println(q);
    for (int i = 0; i < q; ++i) {
        println(queries[i].first, queries[i].second);
    }

    return 0;
}
