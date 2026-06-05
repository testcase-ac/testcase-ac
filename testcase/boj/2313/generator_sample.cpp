#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<int> makeRow(int mode, int len) {
    vector<int> values(len);

    if (mode == 0) {
        for (int& value : values) {
            value = -rnd.next(1, 30);
        }
    } else if (mode == 1) {
        for (int& value : values) {
            value = rnd.next(-2, 2);
        }
    } else if (mode == 2) {
        for (int i = 0; i < len; ++i) {
            int magnitude = rnd.next(1, 25);
            values[i] = (i % 2 == 0 ? magnitude : -magnitude);
        }
        if (rnd.next(2) == 0) {
            reverse(values.begin(), values.end());
        }
    } else if (mode == 3) {
        for (int& value : values) {
            value = -rnd.next(1, 20);
        }
        int left = rnd.next(0, len - 1);
        int right = rnd.next(left, len - 1);
        for (int i = left; i <= right; ++i) {
            values[i] = rnd.next(1, 40);
        }
    } else if (mode == 4) {
        int repeated = rnd.next(-10, 10);
        for (int& value : values) {
            value = repeated;
        }
        if (rnd.next(3) == 0) {
            values[rnd.next(0, len - 1)] = rnd.next(-100, 100);
        }
    } else {
        for (int& value : values) {
            value = rnd.next(-100, 100);
        }
    }

    if (rnd.next(8) == 0) {
        values[rnd.next(0, len - 1)] = rnd.next(-10000, 10000);
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 8);
    if (rnd.next(8) == 0) {
        n = rnd.next(9, 20);
    }

    println(n);
    for (int row = 0; row < n; ++row) {
        int len = rnd.next(1, 12);
        if (rnd.next(10) == 0) {
            len = rnd.next(13, 30);
        }

        int mode = rnd.next(0, 5);
        vector<int> values = makeRow(mode, len);

        println(len);
        println(values);
    }

    return 0;
}
