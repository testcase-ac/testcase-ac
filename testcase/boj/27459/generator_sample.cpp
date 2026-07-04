#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> makeAlternating(int n) {
    vector<int> a(n);
    int x = rnd.next(1, n);
    int y = rnd.next(1, n - 1);
    if (y >= x) ++y;

    for (int i = 0; i < n; ++i) {
        a[i] = (i % 2 == 0) ? x : y;
    }
    return a;
}

static vector<int> makeParityDominated(int n) {
    vector<int> a(n);
    int common = rnd.next(1, n);
    int other = rnd.next(1, n - 1);
    if (other >= common) ++other;

    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0 || rnd.next(0, 3) == 0) {
            a[i] = common;
        } else {
            a[i] = rnd.next(1, n);
            if (a[i] == common) a[i] = other;
        }

        if (i > 0 && a[i] == a[i - 1]) {
            a[i] = other;
            if (a[i] == a[i - 1]) a[i] = common;
        }
    }
    return a;
}

static vector<int> makeLocalBlocks(int n) {
    vector<int> a(n);
    int alphabet = rnd.next(2, min(n, 7));
    for (int i = 0; i < n; ++i) {
        int value;
        if (i >= 2 && rnd.next(0, 2) == 0) {
            value = a[i - 2];
        } else {
            value = rnd.next(1, alphabet);
        }

        if (i > 0 && value == a[i - 1]) {
            value = value % alphabet + 1;
        }
        a[i] = value;
    }
    return a;
}

static vector<int> makePermutationWalk(int n) {
    vector<int> values(n);
    for (int i = 0; i < n; ++i) values[i] = i + 1;
    shuffle(values.begin(), values.end());

    vector<int> a(n);
    int cur = rnd.next(0, n - 1);
    for (int i = 0; i < n; ++i) {
        if (i > 0 && rnd.next(0, 2) == 0) {
            cur = (cur + rnd.next(1, n - 1)) % n;
        } else {
            cur = rnd.next(0, n - 1);
            if (i > 0 && values[cur] == a[i - 1]) cur = (cur + 1) % n;
        }
        a[i] = values[cur];
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    vector<vector<int>> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(2, 24);
        int mode = rnd.next(0, 3);

        if (mode == 0) {
            cases.push_back(makeAlternating(n));
        } else if (mode == 1) {
            cases.push_back(makeParityDominated(n));
        } else if (mode == 2) {
            cases.push_back(makeLocalBlocks(n));
        } else {
            cases.push_back(makePermutationWalk(n));
        }
    }

    println((int)cases.size());
    for (const auto& a : cases) {
        println((int)a.size());
        println(a);
    }

    return 0;
}
