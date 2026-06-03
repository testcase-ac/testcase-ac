#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int t;
    vector<int> values;

    if (mode == 0) {
        t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) values.push_back(rnd.next(1, 30));
    } else if (mode == 1) {
        t = rnd.next(8, 25);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 1) == 0) {
                values.push_back(rnd.next(1, 20));
            } else {
                values.push_back(rnd.next(900, 1000));
            }
        }
    } else if (mode == 2) {
        t = rnd.next(10, 40);
        int base = rnd.next(1, 1000);
        for (int i = 0; i < t; ++i) {
            int delta = rnd.next(-12, 12);
            values.push_back(max(1, min(1000, base + delta)));
        }
    } else if (mode == 3) {
        vector<int> candidates = {1, 2, 3, 4, 5, 7, 8, 10, 16, 20, 31, 32,
                                  63, 64, 100, 127, 128, 255, 256, 511,
                                  512, 999, 1000};
        shuffle(candidates.begin(), candidates.end());
        t = rnd.next(1, (int)candidates.size());
        values.assign(candidates.begin(), candidates.begin() + t);
    } else {
        t = rnd.next(20, 80);
        int step = rnd.next(1, 37);
        int start = rnd.next(1, step);
        for (int i = 0; i < t; ++i) {
            int value = start + step * rnd.next(0, 1000 / step);
            values.push_back(max(1, min(1000, value)));
        }
    }

    println((int)values.size());
    for (int value : values) println(value);

    return 0;
}
