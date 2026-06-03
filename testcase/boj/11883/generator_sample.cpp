#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        values = {1, 2, 3, 4, 5, 6, 7, 8};
    } else if (mode == 1) {
        int base = rnd.next(1, 20);
        for (int r = 0; r < 8; ++r) {
            int n = base * 8 + r;
            if (n <= 1000000) values.push_back(n);
        }
    } else if (mode == 2) {
        int count = rnd.next(8, 30);
        for (int i = 0; i < count; ++i) {
            int a = rnd.next(0, 8);
            int b = rnd.next(0, 8);
            int c = rnd.next(0, 20);
            int n = 3 * a + 5 * b + 8 * c;
            values.push_back(max(1, n));
        }
    } else if (mode == 3) {
        int center = rnd.next(999900, 1000000);
        int count = rnd.next(8, 30);
        for (int i = 0; i < count; ++i) {
            values.push_back(max(1, center - rnd.next(0, 100)));
        }
    } else if (mode == 4) {
        int count = rnd.next(10, 50);
        for (int i = 0; i < count; ++i) {
            values.push_back(rnd.next(1, 1000000));
        }
    } else {
        values = {1, 3, 5, 8, 11, 12, 13, 16, 24, 999999, 1000000};
        int count = rnd.next(5, 20);
        for (int i = 0; i < count; ++i) {
            values.push_back(rnd.next(1, 200));
        }
    }

    shuffle(values.begin(), values.end());
    if ((int)values.size() > 100) values.resize(100);

    println((int)values.size());
    for (int n : values) {
        println(n);
    }

    return 0;
}
