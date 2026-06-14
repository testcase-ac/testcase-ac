#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

void recordMergeSort(vector<int>& a, int left, int right, vector<vector<int>>& states) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    recordMergeSort(a, left, mid, states);
    recordMergeSort(a, mid + 1, right, states);

    vector<int> merged;
    int i = left;
    int j = mid + 1;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) merged.push_back(a[i++]);
        else merged.push_back(a[j++]);
    }
    while (i <= mid) merged.push_back(a[i++]);
    while (j <= right) merged.push_back(a[j++]);

    for (int k = 0; k < static_cast<int>(merged.size()); ++k) {
        a[left + k] = merged[k];
    }
    states.push_back(a);
}

vector<int> makeDistinctArray(int n) {
    vector<int> values;
    int mode = rnd.next(5);

    if (mode == 0) {
        int start = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) values.push_back(start + i);
    } else if (mode == 1) {
        int start = rnd.next(100, 160);
        for (int i = 0; i < n; ++i) values.push_back(start - i);
    } else {
        while (static_cast<int>(values.size()) < n) {
            int candidate = rnd.next(1, 1000000000);
            bool exists = find(values.begin(), values.end(), candidate) != values.end();
            if (!exists) values.push_back(candidate);
        }
    }

    if (mode != 1) {
        shuffle(values.begin(), values.end());
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(6);
    if (sizeMode == 0) n = 5;
    else if (sizeMode <= 3) n = rnd.next(6, 12);
    else n = rnd.next(13, 30);

    vector<int> a = makeDistinctArray(n);
    vector<int> work = a;
    vector<vector<int>> states;
    states.push_back(a);
    recordMergeSort(work, 0, n - 1, states);

    vector<int> b;
    int mode = rnd.next(7);
    if (mode <= 2) {
        b = rnd.any(states);
    } else if (mode == 3) {
        b = rnd.any(states);
        int swaps = rnd.next(1, min(n, 4));
        for (int s = 0; s < swaps; ++s) {
            int i = rnd.next(n);
            int j = rnd.next(n);
            swap(b[i], b[j]);
        }
    } else if (mode == 4) {
        b = a;
        shuffle(b.begin(), b.end());
    } else if (mode == 5) {
        int value = rnd.any(a);
        b.assign(n, value);
    } else {
        for (int i = 0; i < n; ++i) {
            b.push_back(rnd.next(1, 1000000000));
        }
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
