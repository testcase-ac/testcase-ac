#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

const int MAX_A = 1000000000;

vector<int> packCase(int k, const vector<int>& a) {
    vector<int> packed;
    packed.reserve(a.size() + 1);
    packed.push_back(k);
    packed.insert(packed.end(), a.begin(), a.end());
    return packed;
}

vector<int> alreadyEnough() {
    int n = rnd.next(1, 12);
    int k = rnd.next(n, 80);
    vector<int> a(n);
    int remaining = k;
    for (int i = 0; i < n; ++i) {
        int left = n - i - 1;
        int value = rnd.next(1, remaining - left);
        a[i] = value;
        remaining -= value;
    }
    if (rnd.next(2)) {
        shuffle(a.begin(), a.end());
    }
    return packCase(k, a);
}

vector<int> impossibleFirstStep() {
    int n = rnd.next(1, 12);
    int k = rnd.next(1, 40);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.next(k + 1, k + 80);
    }
    if (rnd.next(3) == 0) {
        a[rnd.next(n)] = min(MAX_A, k + rnd.next(1000000, 2000000));
    }
    shuffle(a.begin(), a.end());
    return packCase(k, a);
}

vector<int> greedyChain() {
    int n = rnd.next(3, 18);
    int k = rnd.next(1, 10);
    long long current = k;
    vector<int> a;

    for (int i = 0; i < n; ++i) {
        int lo = 1;
        int hi = (int)min<long long>(current, MAX_A);
        int value;
        if (i > 0 && rnd.next(4) == 0) {
            value = hi;
        } else {
            value = rnd.next(lo, hi);
        }
        a.push_back(value);
        current += value;
    }

    shuffle(a.begin(), a.end());
    return packCase(k, a);
}

vector<int> mixedWithBlocker() {
    int n = rnd.next(4, 16);
    int k = rnd.next(2, 30);
    long long current = k;
    vector<int> a;

    int usable = rnd.next(1, n - 2);
    for (int i = 0; i < usable; ++i) {
        int value = rnd.next(1, (int)min<long long>(current, 60));
        a.push_back(value);
        current += value;
    }

    int blockers = n - usable;
    for (int i = 0; i < blockers; ++i) {
        int value = rnd.next((int)min<long long>(current + 1, MAX_A),
                             (int)min<long long>(current + 80, MAX_A));
        a.push_back(value);
    }

    shuffle(a.begin(), a.end());
    return packCase(k, a);
}

vector<int> nearLimitValues() {
    int n = rnd.next(1, 8);
    int k = rnd.next(900000000, MAX_A);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(2)) {
            a[i] = rnd.next(900000000, MAX_A);
        } else {
            a[i] = rnd.next(1, 100);
        }
    }
    shuffle(a.begin(), a.end());
    return packCase(k, a);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(6, 18);
    println(z);

    for (int tc = 0; tc < z; ++tc) {
        vector<int> packed;
        int mode = rnd.next(5);
        if (mode == 0) {
            packed = alreadyEnough();
        } else if (mode == 1) {
            packed = impossibleFirstStep();
        } else if (mode == 2) {
            packed = greedyChain();
        } else if (mode == 3) {
            packed = mixedWithBlocker();
        } else {
            packed = nearLimitValues();
        }

        int k = packed[0];
        vector<int> a(packed.begin() + 1, packed.end());
        println((int)a.size(), k);
        println(a);
    }

    return 0;
}
