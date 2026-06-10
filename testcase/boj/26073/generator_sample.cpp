#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int randomMultipleInRange(int g) {
    int lo = -100000 / g;
    int hi = 100000 / g;
    return rnd.next(lo, hi) * g;
}

vector<int> makeDistances(int targetGcd, int k) {
    vector<int> values;
    values.reserve(k);

    values.push_back(targetGcd);
    while ((int)values.size() < k) {
        int maxMul = 100000 / targetGcd;
        int mul = rnd.next(1, maxMul);
        values.push_back(targetGcd * mul);
    }

    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 18);
    println(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 7);
        int g = rnd.any(vector<int>{1, 2, 3, 4, 5, 6, 10, 25, 100, 1000, 10000, 50000, 100000});
        int k = rnd.next(1, min(32, max(1, 100000 / g)));

        int x = randomMultipleInRange(g);
        int y = randomMultipleInRange(g);

        if (mode == 0) {
            x = 0;
            y = 0;
        } else if (mode == 1) {
            x = randomMultipleInRange(g);
            y = 0;
        } else if (mode == 2 && g > 1) {
            x = randomMultipleInRange(g);
            int base = randomMultipleInRange(g);
            y = base + rnd.next(1, g - 1);
            if (y > 100000) y -= g;
            if (y < -100000) y += g;
        } else if (mode == 3 && g > 1) {
            int base = randomMultipleInRange(g);
            x = base + rnd.next(1, g - 1);
            if (x > 100000) x -= g;
            if (x < -100000) x += g;
            y = randomMultipleInRange(g);
        } else if (mode == 4) {
            x = rnd.any(vector<int>{-100000, 100000, 0});
            y = rnd.any(vector<int>{-100000, 100000, 0});
        } else if (mode == 5) {
            k = 32;
            g = rnd.any(vector<int>{1, 2, 4, 5, 10, 20, 25, 50});
            x = randomMultipleInRange(g);
            y = randomMultipleInRange(g);
        } else if (mode == 6) {
            k = 1;
            g = rnd.any(vector<int>{1, 7, 11, 97, 99991, 100000});
            x = (rnd.next(0, 1) ? randomMultipleInRange(g) : rnd.next(-100000, 100000));
            y = (rnd.next(0, 1) ? randomMultipleInRange(g) : rnd.next(-100000, 100000));
        }

        println(x, y);
        vector<int> distances = makeDistances(g, k);
        cout << k;
        for (int value : distances) cout << ' ' << value;
        cout << '\n';
    }

    return 0;
}
