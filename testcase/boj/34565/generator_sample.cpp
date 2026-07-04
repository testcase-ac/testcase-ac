#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomByWeights(int n, int hWeight, int yWeight, int qWeight) {
    string s;
    s.reserve(n);
    int total = hWeight + yWeight + qWeight;
    for (int i = 0; i < n; ++i) {
        int pick = rnd.next(1, total);
        if (pick <= hWeight) {
            s += 'H';
        } else if (pick <= hWeight + yWeight) {
            s += 'Y';
        } else {
            s += '?';
        }
    }
    return s;
}

string repeatedPattern(int n, const string& pattern) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += pattern[i % pattern.size()];
    }
    return s;
}

string noisyPattern(int n, string pattern) {
    string s = repeatedPattern(n, pattern);
    int changes = rnd.next(1, max(1, n / 3));
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(0, n - 1);
        s[pos] = rnd.any(string("HY?"));
    }
    return s;
}

int chooseLength(int remaining) {
    if (remaining <= 2) return rnd.next(1, remaining);

    int mode = rnd.next(0, 4);
    int limit = min(remaining, 120);
    if (mode == 0) return rnd.next(1, min(limit, 8));
    if (mode == 1) return rnd.next(1, min(limit, 30));
    if (mode == 2) {
        int maxBlock = max(0, min(limit, 90) / 3);
        return 3 * rnd.next(1, maxBlock);
    }
    if (mode == 3) {
        int maxBlock = max(0, (min(limit, 91) - 1) / 3);
        return 3 * rnd.next(0, maxBlock) + 1;
    }
    int maxBlock = max(0, (min(limit, 92) - 2) / 3);
    return 3 * rnd.next(0, maxBlock) + 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 35);
    vector<string> cases;
    cases.reserve(t);

    int remaining = rnd.next(80, 420);
    for (int tc = 0; tc < t; ++tc) {
        int casesLeft = t - tc;
        int n = chooseLength(remaining - (casesLeft - 1));
        remaining -= n;

        int mode = rnd.next(0, 8);
        string s;
        if (mode == 0) {
            s = string(n, '?');
        } else if (mode == 1) {
            s = randomByWeights(n, 1, 1, 5);
        } else if (mode == 2) {
            s = randomByWeights(n, 5, 1, 1);
        } else if (mode == 3) {
            s = randomByWeights(n, 1, 5, 1);
        } else if (mode == 4) {
            s = noisyPattern(n, "HYH");
        } else if (mode == 5) {
            s = noisyPattern(n, "H?H");
        } else if (mode == 6) {
            s = noisyPattern(n, "?Y?");
        } else if (mode == 7) {
            s = repeatedPattern(n, rnd.any(vector<string>{"H", "Y", "?", "HY", "YH"}));
        } else {
            s = randomByWeights(n, 2, 2, 2);
        }

        cases.push_back(s);
    }

    println((int)cases.size());
    for (const string& s : cases) {
        println((int)s.size());
        println(s);
    }

    return 0;
}
