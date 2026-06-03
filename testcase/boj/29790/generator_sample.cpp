#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int nearValue(int base, int lo, int hi, int radius) {
    return min(hi, max(lo, base + rnd.next(-radius, radius)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 5);
    int n, u, l;

    if (mode == 0) {
        n = nearValue(1000, 1, 130000, 5);
        u = nearValue(8000, 1, 12500, 20);
        l = nearValue(260, 1, 300, 5);
    } else if (mode == 1) {
        n = rnd.any(vector<int>{1, 999, 1000, 1001, 130000});
        u = rnd.next(1, 12500);
        l = rnd.next(1, 300);
    } else if (mode == 2) {
        n = rnd.next(1, 130000);
        u = rnd.any(vector<int>{1, 7999, 8000, 8001, 12500});
        l = rnd.next(1, 300);
    } else if (mode == 3) {
        n = rnd.next(1, 130000);
        u = rnd.next(1, 12500);
        l = rnd.any(vector<int>{1, 259, 260, 261, 300});
    } else if (mode == 4) {
        n = rnd.next(1000, 130000);
        u = rnd.next(8000, 12500);
        l = rnd.next(260, 300);
    } else {
        n = rnd.next(1, 130000);
        u = rnd.next(1, 12500);
        l = rnd.next(1, 300);
    }

    println(n, u, l);
    return 0;
}
