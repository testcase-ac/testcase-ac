#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

string randomString(int m, const string& alphabet) {
    string s;
    for (int i = 0; i < m; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string overlappingNext(const string& prev, const string& alphabet) {
    int m = (int)prev.size();
    string next = randomString(m, alphabet);
    int len = rnd.next(1, m);

    if (rnd.next(2) == 0) {
        for (int i = 0; i < len; ++i) {
            next[i] = prev[m - len + i];
        }
    } else {
        for (int i = 0; i < len; ++i) {
            next[m - len + i] = prev[i];
        }
    }

    return next;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = mode == 0 ? 1 : rnd.next(2, 12);
    int m = mode == 0 ? rnd.next(1, 8) : rnd.next(1, 20);
    vector<string> strings;

    const string low = "abcde";
    const string high = "vwxyz";
    const string broad = "abcdefghijklmnopqrstuvwxyz";

    if (mode == 0) {
        strings.push_back(randomString(m, broad));
    } else if (mode == 1) {
        string s = randomString(m, low);
        strings.push_back(s);
        for (int i = 1; i < n; ++i) {
            strings.push_back(overlappingNext(strings.back(), low));
        }
    } else if (mode == 2) {
        string s = randomString(m, low);
        strings.push_back(s);
        for (int i = 1; i < n; ++i) {
            strings.push_back(overlappingNext(strings.back(), broad));
        }
    } else if (mode == 3) {
        int breakAt = rnd.next(1, n - 1);
        strings.push_back(randomString(m, low));
        for (int i = 1; i < n; ++i) {
            if (i == breakAt) {
                strings.push_back(randomString(m, high));
            } else {
                strings.push_back(overlappingNext(strings.back(), i < breakAt ? low : high));
            }
        }
    } else {
        strings.push_back(randomString(m, low));
        for (int i = 1; i < n; ++i) {
            if (i % 3 == 0) {
                strings.push_back(strings.back());
            } else {
                strings.push_back(overlappingNext(strings.back(), low));
            }
        }
    }

    println(n, m);
    for (const string& s : strings) {
        println(s);
    }

    return 0;
}
