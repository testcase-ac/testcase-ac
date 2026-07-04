#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> constantArray(int n) {
    return vector<int>(n, rnd.next(1, n));
}

vector<int> permutationArray(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    shuffle(a.begin(), a.end());
    return a;
}

vector<int> fewValuesArray(int n) {
    int distinct = rnd.next(2, min(n, 5));
    vector<int> values(n);
    iota(values.begin(), values.end(), 1);
    shuffle(values.begin(), values.end());
    values.resize(distinct);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.any(values);
    }
    return a;
}

vector<int> dominantValueArray(int n) {
    vector<int> a(n, rnd.next(1, n));
    int other = rnd.next(1, n);
    while (other == a[0]) {
        other = rnd.next(1, n);
    }

    int changes = rnd.next(1, max(1, n / 3));
    vector<int> positions(n);
    iota(positions.begin(), positions.end(), 0);
    shuffle(positions.begin(), positions.end());
    for (int i = 0; i < changes; ++i) {
        a[positions[i]] = other;
    }
    return a;
}

vector<int> mixedArray(int n) {
    vector<int> a(n);
    int pivot = rnd.next(1, n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 99) < 45) {
            a[i] = pivot;
        } else {
            a[i] = rnd.next(1, n);
        }
    }
    if (n > 1 && count(a.begin(), a.end(), a[0]) == n) {
        a[rnd.next(0, n - 1)] = a[0] == n ? 1 : a[0] + 1;
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 24);
    vector<vector<int>> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (rnd.next(0, 99) < 75) {
            n = rnd.next(2, 12);
        } else {
            n = rnd.next(13, 30);
        }

        int mode = rnd.next(0, 4);
        if (n == 1) {
            mode = 0;
        }

        if (mode == 0) {
            cases.push_back(constantArray(n));
        } else if (mode == 1) {
            cases.push_back(permutationArray(n));
        } else if (mode == 2) {
            cases.push_back(fewValuesArray(n));
        } else if (mode == 3) {
            cases.push_back(dominantValueArray(n));
        } else {
            cases.push_back(mixedArray(n));
        }
    }

    println(static_cast<int>(cases.size()));
    for (const vector<int>& a : cases) {
        println(static_cast<int>(a.size()));
        println(a);
    }

    return 0;
}
