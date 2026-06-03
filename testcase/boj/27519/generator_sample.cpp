#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t = rnd.next(1, mode == 5 ? 60 : 25);
    vector<int> values;
    values.reserve(t);

    if (mode == 0) {
        for (int i = 0; i < t; ++i) {
            values.push_back(rnd.next(1, 30));
        }
    } else if (mode == 1) {
        int start = rnd.next(1, 200);
        for (int i = 0; i < t; ++i) {
            values.push_back(min(100000, start + i));
        }
    } else if (mode == 2) {
        vector<int> special = {1, 2, 3, 4, 5, 7, 10, 11, 31, 97, 101, 997, 1009};
        for (int i = 0; i < t; ++i) {
            int base = rnd.any(special);
            values.push_back(min(100000, base + rnd.next(0, 3)));
        }
    } else if (mode == 3) {
        int center = rnd.next(1000, 100000);
        for (int i = 0; i < t; ++i) {
            int delta = rnd.next(-20, 20);
            values.push_back(max(1, min(100000, center + delta)));
        }
    } else if (mode == 4) {
        for (int i = 0; i < t; ++i) {
            values.push_back(rnd.next(90000, 100000));
        }
    } else {
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 3) == 0) {
                values.push_back(rnd.next(1, 100));
            } else {
                values.push_back(rnd.next(1, 100000));
            }
        }
    }

    shuffle(values.begin(), values.end());
    println((int)values.size());
    for (int value : values) {
        println(value);
    }

    return 0;
}
