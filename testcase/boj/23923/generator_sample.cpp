#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int wrapValue(long long value, int n) {
    value %= n;
    if (value <= 0) value += n;
    return static_cast<int>(value);
}

vector<int> clusteredValues(int w, int n, int center, int radius) {
    vector<int> values;
    for (int i = 0; i < w; ++i) {
        values.push_back(wrapValue(static_cast<long long>(center) + rnd.next(-radius, radius), n));
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 9);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = (tc == 0 ? 0 : rnd.next(1, 7));
        int w = rnd.next(1, 12);
        int n = rnd.next(2, 60);
        vector<int> values;

        if (mode == 0) {
            w = 1;
            n = rnd.next(2, 10);
            values = {rnd.next(1, n)};
        } else if (mode == 1) {
            int x = rnd.next(1, n);
            values.assign(w, x);
        } else if (mode == 2) {
            int center = rnd.next(1, n);
            int radius = rnd.next(0, min(5, n - 1));
            values = clusteredValues(w, n, center, radius);
        } else if (mode == 3) {
            n = rnd.next(8, 80);
            int radius = rnd.next(1, 4);
            values = clusteredValues(w, n, rnd.any(vector<int>{1, n}), radius);
        } else if (mode == 4) {
            n = 2 * rnd.next(2, 40);
            int a = rnd.next(1, n / 2);
            int b = a + n / 2;
            for (int i = 0; i < w; ++i) {
                values.push_back(rnd.next(0, 1) == 0 ? a : b);
            }
        } else if (mode == 5) {
            n = rnd.next(100000000, 1000000000);
            w = rnd.next(2, 10);
            for (int i = 0; i < w; ++i) {
                values.push_back(rnd.next(1, n));
            }
        } else {
            n = rnd.next(2, 100);
            w = rnd.next(4, 12);
            values.push_back(1);
            values.push_back(n);
            while (static_cast<int>(values.size()) < w) {
                values.push_back(rnd.any(vector<int>{1, n, rnd.next(1, n)}));
            }
            shuffle(values.begin(), values.end());
        }

        println(w, n);
        println(values);
    }

    return 0;
}
