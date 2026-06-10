#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n, l;

    if (mode == 0) {
        n = rnd.next(1, 12);
        l = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.any(vector<int>{1, 2, 3, 299, 300});
        l = rnd.next(1, 300);
    } else if (mode == 2) {
        n = rnd.next(1, 300);
        l = rnd.any(vector<int>{1, 2, 3, 299, 300});
    } else if (mode == 3) {
        n = rnd.next(1, 60);
        l = rnd.next(n, 300);
    } else if (mode == 4) {
        l = rnd.next(1, 60);
        n = rnd.next(l, 300);
    } else if (mode == 5) {
        l = rnd.next(1, 9);
        int full = min(300, (1 << l) - 1);
        n = rnd.next(1, full);
    } else if (mode == 6) {
        int base = rnd.next(1, 300);
        n = max(1, min(300, base + rnd.next(-3, 3)));
        l = max(1, min(300, base + rnd.next(-3, 3)));
    } else if (mode == 7) {
        n = rnd.next(250, 300);
        l = rnd.next(1, 300);
    } else {
        n = rnd.next(1, 300);
        l = rnd.next(250, 300);
    }

    println(n, l);
    return 0;
}
