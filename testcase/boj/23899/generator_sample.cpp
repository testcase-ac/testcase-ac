#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> makeDistinctValues(int n) {
    int start = rnd.next(1, 1000000000 - n + 1);
    vector<int> values(n);
    iota(values.begin(), values.end(), start);
    shuffle(values.begin(), values.end());
    return values;
}

static vector<vector<int>> selectionStates(vector<int> a) {
    vector<vector<int>> states;
    states.push_back(a);

    for (int last = (int)a.size() - 1; last >= 1; --last) {
        int best = 0;
        for (int i = 1; i <= last; ++i) {
            if (a[best] < a[i]) {
                best = i;
            }
        }
        if (best != last) {
            swap(a[best], a[last]);
            states.push_back(a);
        }
    }

    return states;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5) ? rnd.next(25, 80) : rnd.next(5, 18);

    vector<int> a = makeDistinctValues(n);
    if (mode == 1) {
        sort(a.begin(), a.end());
    } else if (mode == 2) {
        sort(a.rbegin(), a.rend());
    }

    vector<int> b;
    vector<vector<int>> states = selectionStates(a);

    if (mode == 0) {
        b = rnd.any(states);
    } else if (mode == 1) {
        b = a;
    } else if (mode == 2) {
        b = rnd.any(states);
    } else if (mode == 3) {
        b = rnd.any(states);
        int swaps = rnd.next(1, min(n, 4));
        for (int i = 0; i < swaps; ++i) {
            int left = rnd.next(0, n - 2);
            int right = rnd.next(left + 1, n - 1);
            swap(b[left], b[right]);
        }
    } else if (mode == 4) {
        b = a;
        shuffle(b.begin(), b.end());
    } else {
        b = makeDistinctValues(n);
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
