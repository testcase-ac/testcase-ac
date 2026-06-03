#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        1, 2, 3, 4, 5, 6, 7, 8,
        999997, 999998, 999999, 1000000,
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        n = rnd.next(1, 40);
    } else if (mode == 2) {
        int r = rnd.next(0, 3);
        int q = rnd.next(0, 25);
        n = 4 * q + r;
        if (n == 0) n += 4;
    } else if (mode == 3) {
        int r = rnd.next(0, 3);
        int q = rnd.next(0, 2500);
        n = 4 * q + r;
        if (n == 0) n += 4;
    } else if (mode == 4) {
        int r = rnd.next(0, 3);
        int maxQ = (1000000 - r) / 4;
        int q = rnd.next(maxQ - 100, maxQ);
        n = 4 * q + r;
    } else {
        n = rnd.next(1, 1000000);
    }

    println(n);
    return 0;
}
