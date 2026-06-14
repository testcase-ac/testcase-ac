#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 16, 25, 27, 30, 31, 32, 36,
        97, 100, 101, 127, 128, 210, 231,
        997, 1000, 1024, 4096, 99991,
        999983, 999999, 1000000
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        n = rnd.next(2, 50);
    } else if (mode == 2) {
        n = rnd.next(51, 5000);
    } else if (mode == 3) {
        int base = rnd.next(2, 1000);
        n = base * rnd.next(2, 1000);
        n = min(n, 1000000);
    } else if (mode == 4) {
        n = 1000000 - rnd.next(0, 1000);
    } else {
        n = rnd.next(2, 1000000);
    }

    println(n);
    return 0;
}
