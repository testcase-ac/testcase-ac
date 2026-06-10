#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int c;
    int e;

    if (mode == 0) {
        n = 1;
        c = 1;
        e = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        int total = n * n;
        c = rnd.next(1, min(total, n + 2));
        e = rnd.next(1, min(total, n + 2));
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        int total = n * n;
        c = rnd.next(max(1, total - 2 * n), total);
        e = rnd.next(1, total);
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        int total = n * n;
        c = rnd.next(1, total);
        e = rnd.next(max(1, total - c + 1), total);
    } else if (mode == 4) {
        n = rnd.next(3, 15);
        int total = n * n;
        int barrier = rnd.next(1, min(total - 2, 2 * n));
        int usable = total - barrier;
        c = rnd.next(1, usable - 1);
        e = usable - c;
    } else if (mode == 5) {
        n = rnd.next(10, 30);
        int total = n * n;
        c = rnd.next(1, total);
        e = rnd.next(1, total);
    } else if (mode == 6) {
        n = rnd.next(90, 100);
        int total = n * n;
        c = rnd.next(max(1, total - 200), total);
        e = rnd.next(max(1, total - 200), total);
    } else {
        n = rnd.next(2, 100);
        int total = n * n;
        vector<int> choices = {1, n, max(1, total / 2), total};
        c = rnd.any(choices);
        e = rnd.any(choices);
    }

    println(n);
    println(c, e);
    return 0;
}
