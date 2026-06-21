#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<long long> splitTotal(int n, long long total, int mode) {
    vector<long long> values(n, 0);
    if (n == 1) {
        values[0] = total;
        return values;
    }

    if (mode == 0) {
        long long remaining = total;
        for (int i = 0; i + 1 < n; ++i) {
            values[i] = rnd.next(0LL, remaining);
            remaining -= values[i];
        }
        values[n - 1] = remaining;
        shuffle(values.begin(), values.end());
    } else if (mode == 1) {
        int maxNonzero = static_cast<int>(min<long long>(n, total));
        int nonzero = rnd.next(1, maxNonzero);
        vector<int> indexes(n);
        for (int i = 0; i < n; ++i) indexes[i] = i;
        shuffle(indexes.begin(), indexes.end());
        for (int i = 0; i < nonzero - 1; ++i) values[indexes[i]] = 1;
        values[indexes[nonzero - 1]] = total - (nonzero - 1);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) values[i] = total / n;
        for (int i = 0; i < total % n; ++i) values[i]++;
        shuffle(values.begin(), values.end());
    } else {
        vector<long long> cuts(n + 1);
        cuts[0] = 0;
        cuts[n] = total;
        for (int i = 1; i < n; ++i) cuts[i] = rnd.next(0LL, total);
        sort(cuts.begin(), cuts.end());
        for (int i = 0; i < n; ++i) values[i] = cuts[i + 1] - cuts[i];
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    long long m;
    if (shape == 0) {
        m = rnd.next(1, 20);
    } else if (shape == 1) {
        m = rnd.next(1, 200);
    } else if (shape == 2) {
        m = rnd.next(900000000LL, 1000000000LL);
    } else {
        m = rnd.next(1, 1000);
    }

    vector<long long> a = splitTotal(n, m, rnd.next(0, 3));
    vector<long long> b;
    if (shape == 3) {
        b = a;
    } else if (shape == 4) {
        b.assign(n, 0);
        b[rnd.next(n)] = m;
    } else {
        b = splitTotal(n, m, rnd.next(0, 3));
    }

    println(n, m);
    println(a);
    println(b);

    return 0;
}
