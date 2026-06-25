#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeDistinctValues(int n) {
    vector<int> pool;
    for (int x = 1; x <= 4 * n + 20; ++x) {
        pool.push_back(x);
    }
    pool.push_back(999999997);
    pool.push_back(999999998);
    pool.push_back(999999999);
    pool.push_back(1000000000);
    shuffle(pool.begin(), pool.end());

    vector<int> values(pool.begin(), pool.begin() + n);
    if (rnd.next(3) == 0) {
        sort(values.begin(), values.end());
    } else if (rnd.next(3) == 0) {
        sort(values.rbegin(), values.rend());
    } else {
        shuffle(values.begin(), values.end());
    }
    return values;
}

static vector<vector<int>> insertionStates(vector<int> a) {
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

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(5, 35);
    vector<int> a = makeDistinctValues(n);
    vector<int> b;

    int mode = rnd.next(6);
    if (mode == 0) {
        b = a;
    } else if (mode == 1) {
        b = a;
        sort(b.begin(), b.end());
    } else if (mode == 2) {
        vector<vector<int>> states = insertionStates(a);
        b = rnd.any(states);
    } else if (mode == 3) {
        b = a;
        sort(b.begin(), b.end());
        int edits = rnd.next(1, min(3, n));
        for (int i = 0; i < edits; ++i) {
            b[rnd.next(n)] = rnd.any(b);
        }
    } else if (mode == 4) {
        b = a;
        shuffle(b.begin(), b.end());
        if (b == a) {
            swap(b[0], b[1]);
        }
    } else {
        b.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(4) == 0) {
                b[i] = rnd.any(a);
            } else {
                b[i] = rnd.next(1, 4 * n + 20);
            }
        }
    }

    println(n);
    println(a);
    println(b);
    return 0;
}
