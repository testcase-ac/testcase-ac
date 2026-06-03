#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long insertionChangeCount(const vector<int>& a) {
    long long changes = 0;
    for (int i = 1; i < (int)a.size(); ++i) {
        int shifts = 0;
        for (int j = i - 1; j >= 0 && a[i] < a[j]; --j) ++shifts;
        if (shifts > 0) changes += shifts + 1;
    }
    return changes;
}

long long chooseK(int n, long long changes) {
    long long maxK = 1LL * n * n;
    int mode = rnd.next(0, 5);

    if (mode == 0) return 1;
    if (mode == 1 && changes > 0) return rnd.next(1LL, changes);
    if (mode == 2 && changes > 0) return changes;
    if (mode == 3 && changes < maxK) return rnd.next(changes + 1, maxK);
    if (mode == 4) return maxK;
    return rnd.next(1LL, maxK);
}

vector<int> makeBaseValues(int n) {
    int mode = rnd.next(0, 3);
    vector<int> values(n);

    if (mode == 0) {
        int start = rnd.next(1, 1000000000 - n + 1);
        for (int i = 0; i < n; ++i) values[i] = start + i;
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) values[i] = i + 1;
    } else {
        int start = 1000000000 - n + 1;
        for (int i = 0; i < n; ++i) values[i] = start + i;
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5)
        n = rnd.next(50, 180);
    else
        n = rnd.next(5, 35);

    vector<int> a = makeBaseValues(n);

    if (mode == 0) {
        // Already sorted: no insertion-sort assignments happen.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        vector<int> zigzag;
        int low = 1;
        int high = n;
        while (low <= high) {
            zigzag.push_back(high-- + 1000);
            if (low <= high) zigzag.push_back(low++ + 1000);
        }
        a = zigzag;
    } else if (mode == 3) {
        int swaps = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < swaps; ++i) {
            int l = rnd.next(0, n - 2);
            int r = rnd.next(l + 1, n - 1);
            swap(a[l], a[r]);
        }
    } else {
        shuffle(a.begin(), a.end());
    }

    long long changes = insertionChangeCount(a);
    long long k = chooseK(n, changes);

    println(n, k);
    println(a);

    return 0;
}
