#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

string periodicString(int n) {
    int period = rnd.next(1, min(8, n));
    string base = randomString(period, "abc");
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(base[i % period]);
    }
    return s;
}

string borderHeavyString(int n) {
    int coreLen = rnd.next(1, max(1, n / 2));
    string core = randomString(coreLen, "abcd");
    string s = core;
    while ((int)s.size() < n) {
        int take = rnd.next(1, min(coreLen, n - (int)s.size()));
        if (rnd.next(2) == 0) {
            s += core.substr(0, take);
        } else {
            s += core.substr(coreLen - take, take);
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 80);
    string s;

    if (mode == 0) {
        s = string(n, rnd.any(string("ab")));
    } else if (mode == 1) {
        s = periodicString(n);
    } else if (mode == 2) {
        s = borderHeavyString(n);
    } else if (mode == 3) {
        s = randomString(n, "abcdefghijklmnopqrstuvwxyz");
    } else {
        string left = randomString((n + 1) / 2, "abcde");
        s = left;
        string right = left;
        reverse(right.begin(), right.end());
        s += right.substr(0, n - (int)s.size());
    }

    int m = rnd.next(1, min(100, max(1, 2 * n)));
    vector<int> queries;
    queries.reserve(m);

    queries.push_back(1);
    if (n > 1) queries.push_back(n);
    if (n > 2) queries.push_back((n + 1) / 2);

    while ((int)queries.size() < m) {
        int queryMode = rnd.next(4);
        if (queryMode == 0) {
            queries.push_back(rnd.next(1, min(n, 8)));
        } else if (queryMode == 1) {
            queries.push_back(rnd.next(max(1, n - 7), n));
        } else {
            queries.push_back(rnd.next(1, n));
        }
    }
    shuffle(queries.begin(), queries.end());

    println(s);
    println(m);
    for (int i = 0; i < m; ++i) {
        println(queries[i]);
    }

    return 0;
}
