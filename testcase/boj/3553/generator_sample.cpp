#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int digits(int x) {
    int result = 0;
    do {
        ++result;
        x /= 10;
    } while (x > 0);
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int d;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = 1;
        d = rnd.next(1, 1000000);
    } else if (mode == 1) {
        d = rnd.next(1, 1000000);
        int width = digits(d);
        n = max(1, width + rnd.next(-1, 2));
    } else if (mode == 2) {
        vector<int> powers = {1, 10, 100, 1000, 10000, 100000, 1000000};
        d = rnd.any(powers);
        n = rnd.next(1, 1000);
    } else if (mode == 3) {
        d = rnd.next(1, 999999);
        d = (d / 10) * 10;
        if (d == 0) d = 10;
        n = rnd.next(1, 1000);
    } else if (mode == 4) {
        n = rnd.any(vector<int>{999, 1000});
        d = rnd.next(1, 1000000);
    } else if (mode == 5) {
        n = rnd.next(1, 6);
        d = rnd.next(1, 1000000);
    } else if (mode == 6) {
        d = rnd.next(900000, 1000000);
        n = rnd.next(1, 1000);
    } else {
        n = rnd.next(1, 1000);
        d = rnd.next(1, 1000000);
    }

    println(n, d);
    return 0;
}
