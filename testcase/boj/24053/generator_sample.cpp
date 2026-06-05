#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<vector<int>> insertionStates(vector<int> a) {
    vector<vector<int>> states;
    states.push_back(a);

    int n = int(a.size());
    for (int i = 1; i < n; ++i) {
        int loc = i - 1;
        int newItem = a[i];
        while (loc >= 0 && newItem < a[loc]) {
            a[loc + 1] = a[loc];
            states.push_back(a);
            --loc;
        }
        if (loc + 1 != i) {
            a[loc + 1] = newItem;
            states.push_back(a);
        }
    }

    return states;
}

vector<int> distinctValues(int n) {
    int mode = rnd.next(4);
    vector<int> a(n);

    if (mode == 0) {
        int start = rnd.next(1, 1000000000 - n + 1);
        iota(a.begin(), a.end(), start);
    } else if (mode == 1) {
        int start = rnd.next(n, 1000000000);
        for (int i = 0; i < n; ++i) a[i] = start - i;
    } else if (mode == 2) {
        int step = rnd.next(2, 1000);
        int start = rnd.next(1, 1000000000 - step * (n - 1));
        for (int i = 0; i < n; ++i) a[i] = start + i * step;
    } else {
        vector<int> pool;
        int limit = rnd.next(n + 5, max(n + 5, min(3 * n + 20, 200000)));
        pool.reserve(limit);
        for (int i = 1; i <= limit; ++i) pool.push_back(i);
        shuffle(pool.begin(), pool.end());
        a.assign(pool.begin(), pool.begin() + n);
        return a;
    }

    shuffle(a.begin(), a.end());
    return a;
}

vector<int> randomB(int n) {
    vector<int> b(n);
    int flavor = rnd.next(3);
    if (flavor == 0) {
        int value = rnd.next(1, 1000000000);
        fill(b.begin(), b.end(), value);
    } else if (flavor == 1) {
        int lo = rnd.next(1, 1000);
        int hi = lo + rnd.next(0, 20);
        for (int& x : b) x = rnd.next(lo, hi);
    } else {
        for (int& x : b) x = rnd.next(1, 1000000000);
    }
    return b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(5, 30);
    if (rnd.next(10) == 0) n = rnd.next(31, 120);

    vector<int> a = distinctValues(n);
    int mode = rnd.next(6);

    if (mode == 1) {
        sort(a.begin(), a.end());
    } else if (mode == 2) {
        sort(a.begin(), a.end(), greater<int>());
    }

    vector<vector<int>> states = insertionStates(a);
    vector<int> b;

    if (mode <= 2 || mode == 3) {
        b = rnd.any(states);
    } else if (mode == 4) {
        b = rnd.any(states);
        int idx = rnd.next(n);
        int delta = rnd.any(vector<int>{-2, -1, 1, 2});
        long long changed = 1LL * b[idx] + delta;
        if (changed < 1) changed = 1;
        if (changed > 1000000000LL) changed = 1000000000LL;
        b[idx] = int(changed);
    } else {
        b = randomB(n);
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
