#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Four categories for diversity:
    // 0: large count of solutions (n in [100,128], count 99..71)
    // 1: moderate count (n in [129,169], count 70..30)
    // 2: small count (n in [170,198], count 29..1)
    // 3: zero count (n in [199,999], count 0)
    int cat = rnd.next(0, 3);
    int n;
    if (cat == 0) {
        n = rnd.next(100, 128);
    } else if (cat == 1) {
        n = rnd.next(129, 169);
    } else if (cat == 2) {
        n = rnd.next(170, 198);
    } else {
        n = rnd.next(199, 999);
    }
    println(n);
    return 0;
}
