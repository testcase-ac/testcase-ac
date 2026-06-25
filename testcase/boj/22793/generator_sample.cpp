#include "testlib.h"

#include <cstdint>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> edgeValues = {
        -2147483647 - 1,
        -2147483647,
        -1000000000,
        -59049,
        -243,
        -81,
        -27,
        -9,
        -3,
        -2,
        -1,
        0,
        1,
        2,
        3,
        9,
        27,
        81,
        243,
        59049,
        1000000000,
        2147483646,
        2147483647,
    };

    int count = rnd.next(1, 18);
    vector<int> values;
    values.reserve(count);

    int mode = rnd.next(0, 4);
    for (int i = 0; i < count; ++i) {
        int value;
        if (mode == 0) {
            value = rnd.next(-30, 30);
        } else if (mode == 1) {
            value = rnd.any(edgeValues);
            if (rnd.next(0, 2) == 0) {
                int delta = rnd.next(-2, 2);
                int64_t shifted = static_cast<int64_t>(value) + delta;
                if (shifted < -2147483648LL) shifted = -2147483648LL;
                if (shifted > 2147483647LL) shifted = 2147483647LL;
                value = static_cast<int>(shifted);
            }
        } else if (mode == 2) {
            int exponent = rnd.next(0, 19);
            int64_t power = 1;
            for (int j = 0; j < exponent; ++j) power *= 3;
            int64_t shifted = power + rnd.next(-5, 5);
            if (rnd.next(0, 1) == 0) shifted = -shifted;
            value = static_cast<int>(shifted);
        } else if (mode == 3) {
            value = rnd.next(-1000000, 1000000);
        } else {
            value = rnd.next(-2147483647 - 1, 2147483647);
        }
        values.push_back(value);
    }

    if (count >= 3 && rnd.next(0, 3) == 0) {
        values[0] = -2147483647 - 1;
        values[1] = 0;
        values[2] = 2147483647;
    }

    for (int value : values) {
        println(value);
    }

    return 0;
}
