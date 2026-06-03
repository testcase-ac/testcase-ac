#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<int> values;

    if (mode == 0) {
        n = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.any(vector<int>{1, 2, 999983, 1000000}));
        }
    } else if (mode == 1) {
        n = rnd.next(8, 40);
        int scale = rnd.next(1, 2000);
        vector<int> pool = {1, 2, 3, 4, 6, 8, 12, 16, 24, 48};
        for (int i = 0; i < n; ++i) {
            values.push_back(scale * rnd.any(pool));
        }
    } else if (mode == 2) {
        n = rnd.next(10, 60);
        int base = rnd.next(1, 500);
        for (int i = 0; i < n; ++i) {
            int multiplier = rnd.next(1, 80);
            values.push_back(base * multiplier);
        }
    } else if (mode == 3) {
        n = rnd.next(12, 70);
        int odd = 2 * rnd.next(0, 40) + 1;
        for (int i = 0; i < n; ++i) {
            int value = odd;
            int power = rnd.next(0, 12);
            for (int j = 0; j < power && value <= 500000; ++j) {
                value *= 2;
            }
            values.push_back(value);
        }
    } else if (mode == 4) {
        n = rnd.next(15, 80);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                values.push_back(rnd.any(vector<int>{1, 1000000}));
            } else {
                values.push_back(rnd.next(1, 1000000));
            }
        }
    } else {
        n = rnd.next(20, 80);
        int scale = rnd.next(1, 20);
        for (int i = 1; i <= n; ++i) {
            values.push_back(scale * i);
        }
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int value : values) {
        println(value);
    }

    return 0;
}
