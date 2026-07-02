#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static int evenInRange(int lo, int hi) {
    if (lo % 2) ++lo;
    if (hi % 2) --hi;
    return lo + 2 * rnd.next((hi - lo) / 2 + 1);
}

static vector<int> majorityCase(int n, int k) {
    vector<int> v(n, 1);
    int minority = rnd.next(1, max(1, n / 2 - 1));
    for (int i = 0; i < minority; ++i) v[i] = rnd.next(2, k);
    shuffle(v.begin(), v.end());
    return v;
}

static vector<int> alternatingCase(int n, int k) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = (i % 2 == 0) ? 1 : rnd.next(2, k);
    }
    if (rnd.next(2)) rotate(v.begin(), v.begin() + rnd.next(n), v.end());
    return v;
}

static vector<int> clusteredCase(int n, int k) {
    vector<int> v;
    while ((int)v.size() < n) {
        int len = rnd.next(1, min(5, n - (int)v.size()));
        int value = rnd.next(1, k);
        if (!v.empty() && value == v.back()) value = value % k + 1;
        for (int i = 0; i < len; ++i) v.push_back(value);
    }
    return v;
}

static vector<int> randomCase(int n, int k) {
    vector<int> v(n);
    int localK = rnd.next(2, k);
    for (int i = 0; i < n; ++i) v[i] = rnd.next(1, localK);
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = rnd.any(vector<int>{2, 4, 6, 8, 10});
    } else {
        n = evenInRange(4, 40);
    }
    int k = rnd.next(2, n);

    vector<int> values;
    if (mode == 0) {
        values.resize(n);
        for (int i = 0; i < n; ++i) values[i] = i % k + 1;
        shuffle(values.begin(), values.end());
    } else if (mode == 1) {
        values = majorityCase(n, k);
    } else if (mode == 2) {
        values = alternatingCase(n, k);
    } else if (mode == 3) {
        values = clusteredCase(n, k);
    } else {
        values = randomCase(n, k);
    }

    println(n, k);
    println(values);
    return 0;
}
