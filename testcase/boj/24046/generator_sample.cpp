#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long countInversions(const vector<int>& a) {
    long long inversions = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = i + 1; j < (int)a.size(); ++j) {
            if (a[i] > a[j]) {
                ++inversions;
            }
        }
    }
    return inversions;
}

int chooseK(long long inversions) {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return 1;
    }
    if (mode == 1 && inversions > 0) {
        return (int)rnd.next(1LL, min(inversions, 100000000LL));
    }
    if (mode == 2 && inversions < 100000000LL) {
        return (int)rnd.next(inversions + 1, min(100000000LL, inversions + 20));
    }
    if (mode == 3) {
        return rnd.next(99999980, 100000000);
    }
    return rnd.next(1, 100000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(5, 30);

    vector<int> values(n);
    int base = rnd.next(1, 1000000000 - 1000);
    int step = rnd.next(1, 17);
    for (int i = 0; i < n; ++i) {
        values[i] = base + i * step;
    }

    if (mode == 0) {
        int swaps = rnd.next(1, min(n - 1, 5));
        for (int i = 0; i < swaps; ++i) {
            int p = rnd.next(0, n - 2);
            swap(values[p], values[p + 1]);
        }
    } else if (mode == 1) {
        reverse(values.begin(), values.end());
    } else if (mode == 2) {
        shuffle(values.begin(), values.end());
    } else if (mode == 3) {
        vector<int> wave;
        for (int i = n - 1; i >= 0; i -= 2) {
            wave.push_back(values[i]);
        }
        for (int i = n % 2; i < n; i += 2) {
            wave.push_back(values[i]);
        }
        values = wave;
    } else {
        rotate(values.begin(), values.begin() + rnd.next(1, n - 1), values.end());
        if (rnd.next(0, 1)) {
            reverse(values.begin(), values.begin() + rnd.next(2, n));
        }
    }

    long long inversions = countInversions(values);
    int k = chooseK(inversions);

    println(n, k);
    println(values);

    return 0;
}
