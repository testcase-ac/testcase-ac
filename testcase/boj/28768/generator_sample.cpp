#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxValue = 1000000000;
    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = rnd.next(1, 20);
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        vector<int> values = {1, 2, 3, 4, 5, 8, 10, 16, 32, 64, 128, 256, 512, 1024};
        n = rnd.any(values);
        m = rnd.any(values);
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        m = rnd.next(1000, 1000000);
    } else if (mode == 3) {
        n = rnd.next(1, 1000000);
        m = rnd.next(maxValue - 1000, maxValue);
    } else if (mode == 4) {
        vector<int> edges = {1, 2, maxValue - 1, maxValue};
        n = rnd.any(edges);
        m = rnd.next(1, maxValue);
    } else {
        n = rnd.next(1, maxValue);
        m = rnd.next(1, maxValue);
    }

    if (rnd.next(0, 1) == 1) {
        swap(n, m);
    }

    println(n, m);
    return 0;
}
