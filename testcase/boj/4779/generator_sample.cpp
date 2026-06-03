#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;

    int mode = rnd.next(0, 3);
    if (mode == 0) {
        int count = rnd.next(1, 6);
        for (int i = 0; i < count; ++i) {
            values.push_back(rnd.next(0, 12));
        }
    } else if (mode == 1) {
        values = {0, 1, 2, 3, 12};
        int extra = rnd.next(0, 4);
        for (int i = 0; i < extra; ++i) {
            values.push_back(rnd.next(8, 12));
        }
        shuffle(values.begin(), values.end());
    } else if (mode == 2) {
        int base = rnd.next(0, 12);
        int count = rnd.next(2, 8);
        for (int i = 0; i < count; ++i) {
            values.push_back(min(12, max(0, base + rnd.next(-2, 2))));
        }
    } else {
        int count = rnd.next(4, 10);
        for (int i = 0; i < count; ++i) {
            if (rnd.next(0, 4) == 0) {
                values.push_back(rnd.any(vector<int>{0, 12}));
            } else {
                values.push_back(rnd.next(1, 11));
            }
        }
    }

    for (int value : values) {
        println(value);
    }

    return 0;
}
