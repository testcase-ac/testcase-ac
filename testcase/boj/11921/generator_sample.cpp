#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    vector<int> values;

    if (mode == 0) {
        n = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(1, 20));
        }
    } else if (mode == 1) {
        n = rnd.next(3, 25);
        int value = rnd.next(1, 10000000);
        values.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(4, 40);
        int lo = rnd.next(1, 50);
        int step = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            values.push_back(min(10000000, lo + i * step));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 60);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(9990000, 10000000));
        }
    } else if (mode == 4) {
        n = rnd.next(10, 80);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(1, 10000000));
        }
    } else {
        n = rnd.next(6, 50);
        for (int i = 0; i < n; ++i) {
            values.push_back(i % 2 == 0 ? 1 : 10000000);
        }
        shuffle(values.begin(), values.end());
    }

    println(n);
    for (int value : values) {
        println(value);
    }

    return 0;
}
