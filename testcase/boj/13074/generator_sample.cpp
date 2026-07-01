#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomEven(int lo, int hi) {
    int loIndex = lo / 2;
    int hiIndex = hi / 2;
    return 2 * rnd.next(loIndex, hiIndex);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        values = {2};
    } else if (mode == 1) {
        values = {2, 4, 6, 8, 10, 12, 98, 100};
    } else if (mode == 2) {
        int center = randomEven(2, 100);
        int radius = rnd.next(0, 4) * 2;
        for (int n = max(2, center - radius); n <= min(100, center + radius); n += 2) {
            values.push_back(n);
        }
    } else if (mode == 3) {
        int t = rnd.next(1, 25);
        for (int i = 0; i < t; ++i) {
            values.push_back(randomEven(2, 100));
        }
    } else {
        int t = rnd.next(20, 80);
        for (int i = 0; i < t; ++i) {
            int band = rnd.next(0, 3);
            if (band == 0) {
                values.push_back(randomEven(2, 20));
            } else if (band == 1) {
                values.push_back(randomEven(40, 70));
            } else {
                values.push_back(randomEven(90, 100));
            }
        }
    }

    shuffle(values.begin(), values.end());

    println(static_cast<int>(values.size()));
    for (int n : values) {
        println(n);
    }

    return 0;
}
