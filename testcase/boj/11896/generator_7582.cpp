#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int MAX = 1000000000;
    int type = rnd.next(0, 5);
    int a = 1, b = 1;
    switch (type) {
        case 0:
            // minimal edge
            a = b = 1;
            break;
        case 1:
            // maximal equal
            a = b = MAX;
            break;
        case 2:
            // small single
            a = rnd.next(1, 100);
            b = a;
            break;
        case 3: {
            // small range
            a = rnd.next(1, 100);
            int extra = rnd.next(0, 100);
            int hi = a + extra;
            b = rnd.next(a, hi);
            break;
        }
        case 4:
            // medium range
            a = rnd.next(1, 1000000);
            b = rnd.next(a, min(a + 1000000, MAX));
            break;
        case 5:
            // large-range spanning upper half
            a = rnd.next(1, MAX / 2);
            b = rnd.next(max(a, MAX / 2), MAX);
            break;
    }
    println(a, b);
    return 0;
}
