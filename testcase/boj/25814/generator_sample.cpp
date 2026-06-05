#include "testlib.h"
#include <vector>

using namespace std;

int weight(int x) {
    int digits = 0;
    int sum = 0;
    while (x > 0) {
        ++digits;
        sum += x % 10;
        x /= 10;
    }
    return digits * sum;
}

int randomNear(int center, int radius) {
    int lo = max(1, center - radius);
    int hi = min(1000000, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> boundary = {
        1, 2, 8, 9, 10, 11, 19, 20, 89, 90, 99, 100, 101, 999,
        1000, 1001, 9999, 10000, 99999, 100000, 999999, 1000000
    };

    int mode = rnd.next(5);
    int a = 1;
    int b = 1;

    if (mode == 0) {
        a = rnd.next(1, 1000000);
        b = rnd.next(1, 1000000);
    } else if (mode == 1) {
        a = randomNear(rnd.any(boundary), rnd.next(0, 25));
        b = randomNear(rnd.any(boundary), rnd.next(0, 25));
    } else if (mode == 2) {
        vector<vector<int>> byWeight(325);
        for (int x = 1; x <= 1000000; ++x) {
            byWeight[weight(x)].push_back(x);
        }

        vector<int> usable;
        for (int w = 0; w < static_cast<int>(byWeight.size()); ++w) {
            if (byWeight[w].size() >= 2) usable.push_back(w);
        }

        int w = rnd.any(usable);
        a = rnd.any(byWeight[w]);
        do {
            b = rnd.any(byWeight[w]);
        } while (a == b);
    } else {
        int want = mode == 3 ? 1 : -1;
        for (int tries = 0; tries < 1000; ++tries) {
            int x = mode == 3 ? rnd.next(1, 1000000) : randomNear(rnd.any(boundary), 1000);
            int y = mode == 3 ? randomNear(rnd.any(boundary), 1000) : rnd.next(1, 1000000);
            int cmp = weight(x) > weight(y) ? 1 : (weight(x) < weight(y) ? -1 : 0);
            if (cmp == want) {
                a = x;
                b = y;
                break;
            }
        }
    }

    println(a, b);
    return 0;
}
