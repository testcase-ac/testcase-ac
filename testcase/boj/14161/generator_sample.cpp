#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxValue = 100000;
    int mode = rnd.next(0, 7);
    int a = 1;
    int b = 1;

    if (mode == 0) {
        a = rnd.next(1, 12);
        b = rnd.next(1, 12);
    } else if (mode == 1) {
        b = rnd.next(2, 20);
        a = rnd.next(1, b - 1);
    } else if (mode == 2) {
        a = rnd.next(1, 30);
        b = 1;
    } else if (mode == 3) {
        a = rnd.next(1, 40);
        b = a;
    } else if (mode == 4) {
        b = rnd.next(2, 60);
        a = b + rnd.next(1, 25);
    } else if (mode == 5) {
        int base = rnd.next(99950, maxValue);
        a = base;
        b = max(1, base - rnd.next(0, 80));
    } else if (mode == 6) {
        a = rnd.any(vector<int>{1, 2, 3, 99999, maxValue});
        b = rnd.any(vector<int>{1, 2, 3, 99999, maxValue});
    } else {
        a = rnd.next(1, maxValue);
        b = rnd.next(1, maxValue);
    }

    println(a, b);
    return 0;
}
