#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

bool isSortedRotation(const vector<int>& values) {
    vector<int> sorted = values;
    sort(sorted.begin(), sorted.end());

    for (int shift = 0; shift < (int)values.size(); ++shift) {
        bool matches = true;
        for (int i = 0; i < (int)values.size(); ++i) {
            if (values[(i + shift) % (int)values.size()] != sorted[i]) {
                matches = false;
                break;
            }
        }
        if (matches) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(mode >= 2 ? 3 : 2, 18));

    vector<int> values;
    if (rnd.next(0, 3) == 0) {
        vector<int> pool;
        for (int x = max(1, 200000 - 4 * n); x <= 200000; ++x) {
            pool.push_back(x);
        }
        shuffle(pool.begin(), pool.end());
        values.assign(pool.begin(), pool.begin() + n);
    } else {
        int limit = rnd.next(n, min(200000, n * 8 + 20));
        vector<int> pool;
        for (int x = 1; x <= limit; ++x) {
            pool.push_back(x);
        }
        shuffle(pool.begin(), pool.end());
        values.assign(pool.begin(), pool.begin() + n);
    }

    sort(values.begin(), values.end());

    if (mode == 1) {
        int shift = rnd.next(1, n - 1);
        rotate(values.begin(), values.begin() + shift, values.end());
    } else if (mode >= 2) {
        do {
            shuffle(values.begin(), values.end());
        } while (isSortedRotation(values));
    }

    println(n);
    println(values);
    return 0;
}
