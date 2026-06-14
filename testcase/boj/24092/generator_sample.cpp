#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

vector<vector<int>> quickSortStates(vector<int> a) {
    vector<vector<int>> states;
    states.push_back(a);

    auto recordSwap = [&](int i, int j) {
        swap(a[i], a[j]);
        states.push_back(a);
    };

    auto partition = [&](int p, int r) -> int {
        int x = a[r];
        int i = p - 1;
        for (int j = p; j < r; ++j) {
            if (a[j] <= x) {
                ++i;
                recordSwap(i, j);
            }
        }
        if (i + 1 != r) {
            recordSwap(i + 1, r);
        }
        return i + 1;
    };

    auto quickSort = [&](auto&& self, int p, int r) -> void {
        if (p >= r) {
            return;
        }
        int q = partition(p, r);
        self(self, p, q - 1);
        self(self, q + 1, r);
    };

    quickSort(quickSort, 0, int(a.size()) - 1);
    return states;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(5, 30);
    if (rnd.next(100) < 12) {
        n = rnd.next(31, 120);
    }

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    int shape = rnd.next(5);
    if (shape == 0) {
        shuffle(a.begin(), a.end());
    } else if (shape == 1) {
        reverse(a.begin(), a.end());
    } else if (shape == 2) {
        int rotations = rnd.next(0, n - 1);
        rotate(a.begin(), a.begin() + rotations, a.end());
    } else if (shape == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = n - i;
        }
        int swaps = rnd.next(1, n);
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(n)], a[rnd.next(n)]);
        }
    }

    int offset = rnd.next(0, 1000000000 - n);
    for (int& value : a) {
        value += offset;
    }

    vector<int> b = a;
    if (mode == 0) {
        // Initial state.
    } else if (mode == 1) {
        vector<vector<int>> states = quickSortStates(a);
        b = states[rnd.next(int(states.size()))];
    } else if (mode == 2) {
        sort(b.begin(), b.end());
    } else if (mode == 3) {
        shuffle(b.begin(), b.end());
    } else if (mode == 4) {
        int base = rnd.any(a);
        for (int& value : b) {
            value = base;
            if (rnd.next(100) < 20) {
                value = rnd.next(1, 1000000000);
            }
        }
    } else {
        int low = rnd.next(1, 1000000000 - n);
        for (int i = 0; i < n; ++i) {
            b[i] = low + i;
        }
        shuffle(b.begin(), b.end());
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
