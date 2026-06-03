#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<int> selectionStateAfter(vector<int> a, int steps) {
    int n = static_cast<int>(a.size());
    for (int last = n - 1; last >= 1 && steps > 0; --last) {
        int maxIndex = 0;
        for (int i = 1; i <= last; ++i) {
            if (a[maxIndex] < a[i]) {
                maxIndex = i;
            }
        }
        if (maxIndex != last) {
            swap(a[maxIndex], a[last]);
            --steps;
        }
    }
    return a;
}

vector<int> distinctValues(int n, int lo, int hi) {
    vector<int> values;
    for (int x = lo; x <= hi; ++x) {
        values.push_back(x);
    }
    shuffle(values.begin(), values.end());
    values.resize(n);
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(5, 24);

    if (mode == 5) {
        n = rnd.next(5, 60);
    }

    vector<int> a = distinctValues(n, 1, max(100, n * 4));
    vector<int> b;

    if (mode == 0) {
        b = a;
    } else if (mode == 1) {
        int steps = rnd.next(0, n - 1);
        b = selectionStateAfter(a, steps);
    } else if (mode == 2) {
        b = a;
        sort(b.begin(), b.end());
    } else if (mode == 3) {
        b = a;
        shuffle(b.begin(), b.end());
    } else if (mode == 4) {
        b = distinctValues(n, 1000000000 - 4 * n, 1000000000);
    } else {
        a = distinctValues(n, 1, n);
        b = a;
        if (rnd.next(2) == 0) {
            reverse(a.begin(), a.end());
        } else {
            shuffle(a.begin(), a.end());
        }
        int steps = rnd.next(0, n - 1);
        b = selectionStateAfter(a, steps);
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
