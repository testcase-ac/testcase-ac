#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXV = 1000000000;

    int mode = rnd.next(8);
    int a = 1;
    int b = 1;

    if (mode == 0) {
        a = rnd.next(1, 100);
        b = a;
    } else if (mode == 1) {
        a = rnd.next(1, 200);
        b = rnd.next(1, 200);
    } else if (mode == 2) {
        int d = rnd.next(1, 1000);
        a = rnd.next(1, MAXV - d);
        b = a + d;
    } else if (mode == 3) {
        vector<int> diffs = {2, 3, 4, 6, 12, 60, 360, 2520, 27720, 720720};
        int d = rnd.any(diffs);
        a = rnd.next(1, MAXV - d);
        b = a + d;
    } else if (mode == 4) {
        int d = rnd.next(1, 100000);
        b = MAXV - rnd.next(0, min(100000, MAXV - d - 1));
        a = b - d;
    } else if (mode == 5) {
        int d = rnd.next(1, 1000000);
        a = rnd.next(1, d);
        b = a + d;
    } else if (mode == 6) {
        a = rnd.next(max(1, MAXV - 1000000), MAXV);
        b = rnd.next(max(1, MAXV - 1000000), MAXV);
    } else {
        int base = rnd.next(1, 1000000);
        int x = rnd.next(1, 1000);
        int y = rnd.next(1, 1000);
        a = base * x;
        b = base * y;
        if (a > MAXV || b > MAXV) {
            a = rnd.next(1, MAXV);
            b = rnd.next(1, MAXV);
        }
    }

    if (rnd.next(2)) swap(a, b);

    println(a, b);
    return 0;
}
