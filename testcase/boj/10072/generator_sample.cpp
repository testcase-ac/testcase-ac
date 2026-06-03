#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

static vector<int> rotatedBase(int n) {
    vector<int> a(n);
    int start = rnd.next(1, n);
    for (int i = 0; i < n; ++i) {
        a[i] = (start + i - 1) % n + 1;
    }
    return a;
}

static void replaceSome(vector<int>& a, int n) {
    int replaceCount = rnd.next(1, min(n, 8));
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        pos[i] = i;
    }
    shuffle(pos.begin(), pos.end());
    sort(pos.begin(), pos.begin() + replaceCount, [&](int x, int y) {
        return a[x] < a[y];
    });
    for (int i = 0; i < replaceCount; ++i) {
        a[pos[i]] = n + i + 1;
    }
}

static vector<int> validSequence(int n) {
    vector<int> a = rotatedBase(n);
    if (n > 1 && rnd.next(0, 1)) {
        replaceSome(a, n);
    }
    return a;
}

static vector<int> invalidSmallOrder(int n) {
    vector<int> a = rotatedBase(n);
    int i = rnd.next(0, n - 1);
    int j = (i + rnd.next(1, n - 1)) % n;
    swap(a[i], a[j]);
    return a;
}

static vector<int> duplicateSequence(int n) {
    vector<int> a = validSequence(n);
    int from = rnd.next(0, n - 1);
    int to = rnd.next(0, n - 1);
    while (to == from) {
        to = rnd.next(0, n - 1);
    }
    a[to] = a[from];
    return a;
}

static vector<int> highOnlySequence(int n) {
    set<int> used;
    vector<int> a;
    while ((int)a.size() < n) {
        int x = rnd.next(n + 1, 250000);
        if (used.insert(x).second) {
            a.push_back(x);
        }
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);
    if (mode == 5) {
        n = rnd.next(95, 120);
    }

    vector<int> a;
    if (mode == 0 || n == 1) {
        a = validSequence(n);
    } else if (mode == 1) {
        a = duplicateSequence(n);
    } else if (mode == 2) {
        a = invalidSmallOrder(n);
    } else if (mode == 3) {
        a = highOnlySequence(n);
    } else {
        a = validSequence(n);
        int changes = rnd.next(1, min(n, 5));
        for (int i = 0; i < changes; ++i) {
            a[rnd.next(0, n - 1)] = rnd.next(1, 250000);
        }
    }

    println(n);
    println(a);
    return 0;
}
