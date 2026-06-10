#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> h(n);
    iota(h.begin(), h.end(), 1);
    return h;
}

static vector<int> makeAlternatingExtremes(int n) {
    vector<int> h;
    h.reserve(n);
    int lo = 1;
    int hi = n;
    while (lo <= hi) {
        if (rnd.next(0, 1) == 0) {
            h.push_back(hi--);
            if (lo <= hi) h.push_back(lo++);
        } else {
            h.push_back(lo++);
            if (lo <= hi) h.push_back(hi--);
        }
    }
    return h;
}

static vector<int> makeMountain(int n) {
    vector<int> h = identityPermutation(n);
    int peak = rnd.next(0, n - 1);
    vector<int> small;
    small.reserve(n - 1);
    for (int value = 1; value < n; ++value) small.push_back(value);
    shuffle(small.begin(), small.end());

    vector<int> left(small.begin(), small.begin() + peak);
    vector<int> right(small.begin() + peak, small.end());
    sort(left.begin(), left.end());
    sort(right.rbegin(), right.rend());

    h.clear();
    h.insert(h.end(), left.begin(), left.end());
    h.push_back(n);
    h.insert(h.end(), right.begin(), right.end());
    return h;
}

static vector<int> makeBlockwise(int n) {
    vector<int> h = identityPermutation(n);
    int blockSize = rnd.next(2, min(n, 8));
    for (int first = 0; first < n; first += blockSize) {
        int last = min(n, first + blockSize);
        if (rnd.next(0, 1) == 0) {
            reverse(h.begin() + first, h.begin() + last);
        } else {
            shuffle(h.begin() + first, h.begin() + last);
        }
    }
    return h;
}

static vector<int> makeNearlySorted(int n) {
    vector<int> h = identityPermutation(n);
    int swaps = rnd.next(1, max(1, n / 4));
    for (int i = 0; i < swaps; ++i) {
        int pos = rnd.next(0, n - 1);
        int delta = rnd.next(-3, 3);
        int other = max(0, min(n - 1, pos + delta));
        swap(h[pos], h[other]);
    }
    return h;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (rnd.next(0, 9) == 0) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(2, 30);
    }

    vector<int> h = identityPermutation(n);
    if (mode == 0) {
        // Single cow edge case.
    } else if (mode == 1) {
        reverse(h.begin(), h.end());
    } else if (mode == 2) {
        h = makeMountain(n);
    } else if (mode == 3) {
        h = makeAlternatingExtremes(n);
    } else if (mode == 4) {
        h = makeBlockwise(n);
    } else if (mode == 5) {
        h = makeNearlySorted(n);
    } else {
        shuffle(h.begin(), h.end());
    }

    println(n);
    println(h);
    return 0;
}
