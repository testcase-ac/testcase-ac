#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int count = rnd.next(1, 12);
    vector<int> values;

    if (mode == 0) {
        count = rnd.next(1, 6);
        for (int i = 0; i < count; ++i) {
            values.push_back(rnd.next(1, 6));
        }
    } else if (mode == 1) {
        count = rnd.next(2, 8);
        for (int i = 0; i < count; ++i) {
            values.push_back(rnd.next(18, 23));
        }
    } else if (mode == 2) {
        count = rnd.next(2, 10);
        values.push_back(1);
        values.push_back(23);
        for (int i = 2; i < count; ++i) {
            values.push_back(rnd.next(1, 23));
        }
        shuffle(values.begin(), values.end());
    } else if (mode == 3) {
        count = rnd.next(3, 12);
        int repeated = rnd.next(1, 23);
        for (int i = 0; i < count; ++i) {
            values.push_back(rnd.next(0, 3) == 0 ? rnd.next(1, 23) : repeated);
        }
    } else {
        count = rnd.next(1, 12);
        for (int i = 0; i < count; ++i) {
            values.push_back(rnd.next(1, 23));
        }
    }

    for (int n : values) {
        println(n);
    }
    println(-1);

    return 0;
}
