#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int a = 1000;
    int b = 1000;

    if (mode == 0) {
        a = b = rnd.next(1000, 9999);
    } else if (mode == 1) {
        a = rnd.next(1000, 9989);
        b = a + rnd.next(1, 10);
    } else if (mode == 2) {
        vector<int> centers = {1000, 1010, 1090, 1100, 1900, 2000, 9000, 9900, 9990, 9999};
        int center = rnd.any(centers);
        a = max(1000, center - rnd.next(0, 20));
        b = min(9999, center + rnd.next(0, 20));
    } else if (mode == 3) {
        int block = rnd.next(10, 99) * 100;
        a = max(1000, block - rnd.next(0, 30));
        b = min(9999, block + rnd.next(0, 130));
    } else if (mode == 4) {
        a = rnd.next(1000, 8999);
        b = min(9999, a + rnd.next(100, 1000));
    } else if (mode == 5) {
        a = rnd.next(1000, 1500);
        b = rnd.next(9500, 9999);
    } else {
        a = rnd.next(1000, 9999);
        b = rnd.next(a, 9999);
    }

    int d;
    if (rnd.next(0, 3) == 0) {
        d = rnd.any(vector<int>{0, 1, 9});
    } else {
        d = rnd.next(0, 9);
    }

    println(a, b, d);
    return 0;
}
