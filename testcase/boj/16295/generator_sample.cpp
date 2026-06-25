#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int maxPairs = n * (n - 1) / 2;
    int mMode = rnd.next(4);
    int m;
    if (mMode == 0) {
        m = rnd.next(1, min(6, maxPairs));
    } else if (mMode == 1) {
        int upper = min(40, maxPairs + 8);
        int lower = max(1, min(upper, maxPairs - 4));
        m = rnd.next(lower, upper);
    } else {
        m = rnd.next(1, min(30, maxPairs + 10));
    }

    vector<int> x(n);
    int positionMode = rnd.next(4);
    if (positionMode == 0) {
        x[0] = rnd.next(0, 5);
        for (int i = 1; i < n; ++i) {
            x[i] = x[i - 1] + rnd.next(1, 5);
        }
    } else if (positionMode == 1) {
        x[0] = rnd.next(0, 20);
        for (int i = 1; i < n; ++i) {
            x[i] = x[i - 1] + rnd.next(1, 100);
        }
    } else if (positionMode == 2) {
        int spanLimit = 100 * (n - 1);
        x[0] = 1000000000 - spanLimit - rnd.next(0, 1000);
        for (int i = 1; i < n; ++i) {
            x[i] = x[i - 1] + rnd.next(1, 100);
        }
    } else {
        x[0] = 0;
        for (int i = 1; i < n; ++i) {
            x[i] = x[i - 1] + rnd.any(vector<int>{1, 2, 3, 10, 1000, 1000000});
        }
    }

    vector<int> distances;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            distances.push_back(x[j] - x[i]);
        }
    }

    vector<int> lengths;
    int lengthMode = rnd.next(5);
    for (int i = 0; i < m; ++i) {
        int value;
        if (lengthMode == 0) {
            value = rnd.next(1, max(1, min(30, x.back() - x.front())));
        } else if (lengthMode == 1) {
            value = rnd.any(distances);
        } else if (lengthMode == 2) {
            int base = rnd.any(distances);
            value = max(1, min(1000000000, base + rnd.next(-3, 3)));
        } else if (lengthMode == 3) {
            value = rnd.next(max(1, x.back() - x.front()), 1000000000);
        } else {
            int localMode = rnd.next(4);
            if (localMode == 0) {
                value = rnd.any(distances);
            } else if (localMode == 1) {
                value = max(1, rnd.any(distances) - rnd.next(0, 2));
            } else if (localMode == 2) {
                value = min(1000000000, rnd.any(distances) + rnd.next(0, 5));
            } else {
                value = rnd.next(1, 1000000000);
            }
        }
        lengths.push_back(value);
    }

    shuffle(lengths.begin(), lengths.end());

    println(n, m);
    println(x);
    println(lengths);
    return 0;
}
