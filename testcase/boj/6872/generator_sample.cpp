#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a;
    int b;
    int mode = rnd.next(6);

    if (mode == 0) {
        a = b = rnd.next(1, 999);
    } else if (mode == 1) {
        a = rnd.next(1, 980);
        b = rnd.next(a, min(999, a + rnd.next(1, 20)));
    } else if (mode == 2) {
        vector<int> centers = {1, 4, 6, 8, 10, 11, 12, 14, 15, 16, 25, 27, 49, 121, 997};
        int center = rnd.any(centers);
        int radius = rnd.next(0, 8);
        a = max(1, center - rnd.next(0, radius));
        b = min(999, center + rnd.next(0, radius));
    } else if (mode == 3) {
        a = rnd.next(1, 700);
        b = rnd.next(a + 100, 999);
    } else if (mode == 4) {
        a = rnd.next(900, 999);
        b = rnd.next(a, 999);
    } else {
        a = rnd.next(1, 999);
        b = rnd.next(1, 999);
        if (a > b) swap(a, b);
    }

    println(a);
    println(b);

    return 0;
}
