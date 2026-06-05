#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int weightedLeg() {
    if (rnd.next(100) < 70) {
        return rnd.next(1, 12);
    }
    return rnd.next(1, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int b = weightedLeg();
    int d = weightedLeg();
    int c = weightedLeg();
    int l = rnd.next(0, 250);

    if (mode == 0) {
        b = rnd.next(1, 6);
        d = rnd.next(1, 6);
        c = rnd.next(1, 6);
        l = rnd.next(0, 40);
    } else if (mode == 1) {
        vector<int> values = {1, 2, 4, 6, 10, 25, 50, 80, 100};
        b = rnd.any(values);
        d = rnd.any(values);
        c = rnd.any(values);
        l = rnd.next(0, 250);
    } else if (mode == 2) {
        b = rnd.next(1, 20);
        d = rnd.next(1, 20);
        c = rnd.next(1, 20);
        int x = rnd.next(0, 12);
        int y = rnd.next(0, 12);
        int z = rnd.next(0, 12);
        l = min(250, x * b + y * d + z * c);
    } else if (mode == 3) {
        int common = rnd.next(2, 20);
        b = common * rnd.next(1, 100 / common);
        d = common * rnd.next(1, 100 / common);
        c = common * rnd.next(1, 100 / common);
        l = common * rnd.next(0, 250 / common);
        if (rnd.next(2) == 0 && l < 250) {
            ++l;
        }
    } else if (mode == 4) {
        b = rnd.next(1, 100);
        d = b;
        c = rnd.next(1, 100);
        l = rnd.next(0, 250);
    } else {
        vector<int> values = {1, 99, 100};
        b = rnd.any(values);
        d = rnd.any(values);
        c = rnd.any(values);
        l = rnd.any(vector<int>{0, 1, 249, 250});
    }

    println(b, d, c, l);
    return 0;
}
