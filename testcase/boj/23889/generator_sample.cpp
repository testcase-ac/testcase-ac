#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> pickStarts(int n, int k, int mode) {
    vector<int> starts;

    if (mode == 0) {
        for (int i = 1; i <= k; ++i) starts.push_back(i);
    } else if (mode == 1) {
        for (int i = n - k + 1; i <= n; ++i) starts.push_back(i);
    } else if (mode == 2 && k == n) {
        for (int i = 1; i <= n; ++i) starts.push_back(i);
    } else {
        vector<int> candidates;
        for (int i = 1; i <= n; ++i) candidates.push_back(i);
        shuffle(candidates.begin(), candidates.end());
        candidates.resize(k);
        sort(candidates.begin(), candidates.end());
        starts = candidates;
    }

    return starts;
}

vector<int> buildWeights(int n, int mode) {
    vector<int> x(n);

    if (mode == 0) {
        int value = rnd.next(1, 9);
        fill(x.begin(), x.end(), value);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) x[i] = (i % 2 == 0 ? rnd.next(1, 3) : rnd.next(9000, 10000));
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) x[i] = rnd.next(1, 20);
        x[rnd.next(n)] = 10000;
    } else {
        for (int i = 0; i < n; ++i) x[i] = rnd.next(1, 10000);
    }

    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 6);
    } else if (sizeMode == 2) {
        n = rnd.next(7, 15);
    } else if (sizeMode == 3) {
        n = rnd.next(16, 30);
    } else {
        n = rnd.next(40, 80);
    }

    int kMode = rnd.next(4);
    int k;
    if (n == 1 || kMode == 0) {
        k = n;
    } else if (kMode == 1) {
        k = 1;
    } else if (kMode == 2) {
        k = rnd.next(1, min(n, 5));
    } else {
        k = rnd.next(1, n);
    }

    int mMode = rnd.next(4);
    int m;
    if (mMode == 0) {
        m = k;
    } else if (mMode == 1) {
        m = 1;
    } else {
        m = rnd.next(1, k);
    }

    vector<int> x = buildWeights(n, rnd.next(4));
    vector<int> starts = pickStarts(n, k, rnd.next(4));

    println(n, m, k);
    println(x);
    println(starts);

    return 0;
}
