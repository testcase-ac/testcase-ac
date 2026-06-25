#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<vector<int>> selectionStates(vector<int> a, int q) {
    vector<vector<int>> states;
    states.push_back(a);

    int left = 0;
    int right = int(a.size()) - 1;
    while (left < right) {
        int pivot = a[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (a[j] <= pivot) {
                ++i;
                if (i != j) {
                    swap(a[i], a[j]);
                    states.push_back(a);
                }
            }
        }
        if (i + 1 != right) {
            swap(a[i + 1], a[right]);
            states.push_back(a);
        }

        int rank = i + 1 - left + 1;
        if (q < rank) {
            right = i;
        } else if (q == rank) {
            break;
        } else {
            q -= rank;
            left = i + 2;
        }
    }

    return states;
}

static vector<int> distinctValues(int n, int lo, int step) {
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = lo + i * step;
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(5, 30);
    int q = rnd.next(1, n);

    vector<int> a = distinctValues(n, 1, rnd.next(1, 7));
    int arrangement = rnd.next(5);
    if (arrangement == 0) {
        reverse(a.begin(), a.end());
    } else if (arrangement == 1) {
        rotate(a.begin(), a.begin() + rnd.next(n), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }

    vector<vector<int>> states = selectionStates(a, q);
    vector<int> b;
    int mode = rnd.next(4);
    if (mode == 0) {
        b = a;
    } else if (mode == 1) {
        b = states[rnd.next(int(states.size()))];
    } else if (mode == 2) {
        b = a;
        shuffle(b.begin(), b.end());
    } else {
        b = distinctValues(n, 1000000000 - n * 3, 3);
        shuffle(b.begin(), b.end());
    }

    println(n, q);
    println(a);
    println(b);

    return 0;
}
