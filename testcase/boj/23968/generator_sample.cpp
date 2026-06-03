#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long inversionCount(const vector<long long>& a) {
    long long total = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = i + 1; j < (int)a.size(); ++j) {
            if (a[i] > a[j]) ++total;
        }
    }
    return total;
}

long long chooseK(int n, long long inversions) {
    int mode = rnd.next(0, 5);
    long long limit = 1LL * n * n;

    if (mode == 0) return 1;
    if (mode == 1 && inversions > 0) return rnd.next(1LL, inversions);
    if (mode == 2) return min(limit, inversions + 1);
    if (mode == 3) return limit;
    if (mode == 4 && inversions > 0) return inversions;
    return rnd.next(1LL, limit);
}

vector<long long> makeValues(int n, int mode) {
    vector<long long> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        return a;
    }

    if (mode == 1) {
        reverse(a.begin(), a.end());
        return a;
    }

    if (mode == 2) {
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            int pos = rnd.next(0, n - 2);
            swap(a[pos], a[pos + 1]);
        }
        return a;
    }

    if (mode == 3) {
        shuffle(a.begin(), a.end());
        return a;
    }

    long long start = 1000000000LL - n + 1;
    for (int i = 0; i < n; ++i) a[i] = start + i;
    if (mode == 4) {
        reverse(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 5;
    } else if (sizeMode == 1) {
        n = rnd.next(6, 12);
    } else if (sizeMode == 2) {
        n = rnd.next(13, 35);
    } else {
        n = rnd.next(36, 100);
    }

    int valueMode = rnd.next(0, 5);
    vector<long long> a = makeValues(n, valueMode);
    long long k = chooseK(n, inversionCount(a));

    println(n, k);
    println(a);

    return 0;
}
