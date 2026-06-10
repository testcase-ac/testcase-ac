#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeRandomArray(int n) {
    int maxValue = rnd.next(1, n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.next(1, maxValue);
    }
    return a;
}

vector<int> makePermutationLike(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    if (rnd.next(2)) {
        reverse(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }
    return a;
}

vector<int> makeValidNested(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = 1;
    }

    int layers = rnd.next(1, min(n, 6));
    for (int value = layers; value >= 1; --value) {
        int left = layers - value;
        int right = n - 1 - (layers - value);
        if (left > right) {
            break;
        }
        a[left] = value;
        a[right] = value;
    }

    for (int i = 0; i < n; ++i) {
        if (a[i] == 1 && rnd.next(3) == 0) {
            a[i] = 1;
        }
    }
    return a;
}

vector<int> makeEqualBlocks(int n) {
    vector<int> a;
    int value = 1;
    while ((int)a.size() < n) {
        int len = rnd.next(1, min(4, n - (int)a.size()));
        for (int i = 0; i < len; ++i) {
            a.push_back(value);
        }
        ++value;
    }
    if (rnd.next(2)) {
        reverse(a.begin(), a.end());
    }
    return a;
}

vector<int> makeGapViolation(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.next(1, n);
    }

    int low = rnd.next(1, max(1, n - 1));
    int high = rnd.next(low + 1, n);
    int left = rnd.next(0, n - 3);
    int mid = rnd.next(left + 1, n - 2);
    int right = rnd.next(mid + 1, n - 1);
    a[left] = low;
    a[mid] = high;
    a[right] = low;
    return a;
}

vector<int> makeAlternatingTrap(int n) {
    vector<int> a(n);
    int low = rnd.next(1, max(1, n / 2));
    int high = rnd.next(low, n);
    for (int i = 0; i < n; ++i) {
        a[i] = (i % 2 == 0 ? low : high);
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 14);
    vector<vector<int>> tests;

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else {
            n = rnd.next(2, 18);
        }

        int mode = rnd.next(6);
        vector<int> a;
        if (mode == 0) {
            a = makeRandomArray(n);
        } else if (mode == 1) {
            a = makePermutationLike(n);
        } else if (mode == 2) {
            a = makeValidNested(n);
        } else if (mode == 3) {
            a = makeEqualBlocks(n);
        } else if (mode == 4 && n >= 3) {
            a = makeGapViolation(n);
        } else if (n >= 3) {
            a = makeAlternatingTrap(n);
        } else {
            a = makeRandomArray(n);
        }

        tests.push_back(a);
    }

    println((int)tests.size());
    for (const vector<int>& a : tests) {
        println((int)a.size());
        println(a);
    }

    return 0;
}
