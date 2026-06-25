#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

static string makeString(int n) {
    int mode = rnd.next(0, 4);
    string s;
    s.reserve(n);

    if (mode == 0) {
        char c = char('a' + rnd.next(0, 25));
        s.assign(n, c);
    } else if (mode == 1) {
        int alphabet = rnd.next(1, min(26, max(1, n)));
        for (int i = 0; i < n; ++i) {
            s.push_back(char('a' + rnd.next(0, alphabet - 1)));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            s.push_back(char('a' + (i % 26)));
        }
        if (rnd.next(0, 1)) {
            reverse(s.begin(), s.end());
        }
    } else if (mode == 3) {
        string letters = "abcdefghijklmnopqrstuvwxyz";
        shuffle(letters.begin(), letters.end());
        int alphabet = rnd.next(2, min(26, max(2, n)));
        for (int i = 0; i < n; ++i) {
            s.push_back(letters[rnd.next(0, alphabet - 1)]);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            s.push_back(char('a' + rnd.next(0, 25)));
        }
        sort(s.begin(), s.end());
        if (rnd.next(0, 1)) {
            reverse(s.begin(), s.end());
        }
    }

    return s;
}

static vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

static vector<int> longCyclePermutation(int n) {
    vector<int> order = identityPermutation(n);
    shuffle(order.begin(), order.end());

    vector<int> p(n + 1);
    for (int i = 0; i < n; ++i) {
        p[order[i]] = order[(i + 1) % n];
    }

    return vector<int>(p.begin() + 1, p.end());
}

static vector<int> pairedSwapPermutation(int n) {
    vector<int> order = identityPermutation(n);
    shuffle(order.begin(), order.end());

    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
    for (int i = 0; i + 1 < n; i += 2) {
        p[order[i]] = order[i + 1];
        p[order[i + 1]] = order[i];
    }

    return vector<int>(p.begin() + 1, p.end());
}

static vector<int> mixedCyclePermutation(int n) {
    vector<int> order = identityPermutation(n);
    shuffle(order.begin(), order.end());

    vector<int> p(n + 1);
    int pos = 0;
    while (pos < n) {
        int remaining = n - pos;
        int len = rnd.next(1, min(remaining, rnd.next(2, 8)));
        for (int i = 0; i < len; ++i) {
            p[order[pos + i]] = order[pos + (i + 1) % len];
        }
        pos += len;
    }

    return vector<int>(p.begin() + 1, p.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 3) {
        n = rnd.next(2, 8);
    } else if (sizeMode <= 7) {
        n = rnd.next(9, 30);
    } else {
        n = rnd.next(31, 80);
    }

    int kMode = rnd.next(0, 5);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = rnd.next(2, 30);
    } else if (kMode == 2) {
        k = rnd.next(31, 1000);
    } else if (kMode == 3) {
        k = 1000000000;
    } else if (kMode == 4) {
        k = 1000000000 - rnd.next(0, 1000);
    } else {
        k = rnd.next(1, 1000000000);
    }

    vector<int> p;
    int permMode = rnd.next(0, 4);
    if (permMode == 0) {
        p = identityPermutation(n);
    } else if (permMode == 1) {
        p = longCyclePermutation(n);
    } else if (permMode == 2) {
        p = pairedSwapPermutation(n);
    } else if (permMode == 3) {
        p = mixedCyclePermutation(n);
    } else {
        p = identityPermutation(n);
        shuffle(p.begin(), p.end());
    }

    println(n, k);
    println(makeString(n));
    println(p);

    return 0;
}
