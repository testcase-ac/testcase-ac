#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<long long> distinctValues(int n) {
    vector<long long> values;
    values.reserve(n);

    long long start = rnd.next(1, 1000000);
    long long step = rnd.next(1, 17);
    for (int i = 0; i < n; ++i) values.push_back(start + step * i);
    shuffle(values.begin(), values.end());
    return values;
}

static vector<vector<long long>> bubbleStates(vector<long long> a) {
    int n = (int)a.size();
    vector<vector<long long>> states;
    states.push_back(a);

    for (int last = n - 1; last >= 1; --last) {
        for (int i = 0; i < last; ++i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                states.push_back(a);
            }
        }
    }

    return states;
}

static vector<long long> makeUnreachablePermutation(const vector<long long>& a) {
    vector<vector<long long>> states = bubbleStates(a);
    vector<long long> b = a;

    for (int attempt = 0; attempt < 200; ++attempt) {
        b = a;
        shuffle(b.begin(), b.end());
        if (find(states.begin(), states.end(), b) == states.end()) return b;
    }

    sort(b.begin(), b.end());
    if ((int)b.size() >= 2) swap(b[0], b[1]);
    return b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(5, 30);
    if (mode == 5) n = rnd.next(40, 120);

    vector<long long> a = distinctValues(n);
    vector<long long> b;

    if (mode == 1) {
        sort(a.rbegin(), a.rend());
    } else if (mode == 2) {
        sort(a.begin(), a.end());
        int swaps = rnd.next(1, min(8, n - 1));
        for (int k = 0; k < swaps; ++k) {
            int i = rnd.next(0, n - 2);
            if (a[i] < a[i + 1]) swap(a[i], a[i + 1]);
        }
    }

    vector<vector<long long>> states = bubbleStates(a);

    if (mode == 0) {
        b = a;
    } else if (mode == 1) {
        b = states[rnd.next((int)states.size())];
    } else if (mode == 2) {
        b = states[rnd.next((int)states.size())];
    } else if (mode == 3) {
        b = makeUnreachablePermutation(a);
    } else if (mode == 4) {
        b = distinctValues(n);
    } else if (mode == 5) {
        b = makeUnreachablePermutation(a);
    } else {
        b = states.back();
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
