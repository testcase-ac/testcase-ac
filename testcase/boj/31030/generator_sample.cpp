#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> buildPermutationFromCycles(vector<int> labels, const vector<int>& lengths) {
    vector<int> a(labels.size() + 1);
    int offset = 0;
    for (int len : lengths) {
        vector<int> cycle(labels.begin() + offset, labels.begin() + offset + len);
        shuffle(cycle.begin(), cycle.end());
        for (int i = 0; i < len; ++i) {
            a[cycle[i]] = cycle[(i + 1) % len];
        }
        offset += len;
    }
    return a;
}

static vector<int> chooseCycleLengths(int n, int mode) {
    vector<int> lengths;
    if (mode == 0) {
        lengths.assign(n, 1);
    } else if (mode == 1) {
        lengths.push_back(n);
    } else if (mode == 2) {
        int remaining = n;
        while (remaining > 0) {
            int len = min(remaining, rnd.next(1, 3));
            lengths.push_back(len);
            remaining -= len;
        }
    } else if (mode == 3) {
        int base = rnd.any(vector<int>{2, 3, 4, 5, 6});
        int remaining = n;
        while (remaining > 0) {
            int len = min(remaining, base * rnd.next(1, 3));
            lengths.push_back(len);
            remaining -= len;
        }
    } else {
        int remaining = n;
        while (remaining > 0) {
            int cap = min(remaining, 10);
            int len = rnd.next(1, cap);
            lengths.push_back(len);
            remaining -= len;
        }
    }
    shuffle(lengths.begin(), lengths.end());
    return lengths;
}

static vector<long long> chooseWeights(int n, int mode) {
    vector<long long> x(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) x[i] = i + 1;
        shuffle(x.begin(), x.end());
    } else if (mode == 1) {
        long long low = rnd.next(1, 1000);
        long long high = rnd.next(999999000, 1000000000);
        for (int i = 0; i < n; ++i) x[i] = (rnd.next(2) == 0 ? low : high);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) x[i] = rnd.next(1, 20);
    } else {
        for (int i = 0; i < n; ++i) x[i] = rnd.next(1, 1000000000);
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
    } else {
        n = rnd.next(3, 45);
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());

    vector<int> lengths = chooseCycleLengths(n, mode);
    vector<int> a = buildPermutationFromCycles(labels, lengths);
    vector<long long> x = chooseWeights(n, rnd.next(0, 3));

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    println(x);

    return 0;
}
