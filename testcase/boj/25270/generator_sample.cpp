#include "testlib.h"
#include <vector>
using namespace std;

int normalized(int n) {
    if (n < 1) return 1;
    if (n > 10000) return 10000;
    if (n % 100 == 99) {
        if (n == 9999) return 10000;
        return n + 1;
    }
    return n;
}

int aroundEnding99(int center) {
    int offset = rnd.next(-55, 55);
    if (offset == 0) offset = rnd.any(vector<int>{-1, 1});
    return normalized(center + offset);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 98);
    } else if (mode == 1) {
        int center = 99 + 100 * rnd.next(0, 98);
        n = aroundEnding99(center);
    } else if (mode == 2) {
        int center = 99 + 100 * rnd.next(0, 98);
        n = normalized(center + rnd.any(vector<int>{-50, 50}));
    } else if (mode == 3) {
        n = rnd.next(9900, 10000);
        n = normalized(n);
    } else if (mode == 4) {
        n = 100 * rnd.next(1, 100);
    } else {
        do {
            n = rnd.next(1, 10000);
        } while (n % 100 == 99);
    }

    println(n);
    return 0;
}
