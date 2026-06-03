#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 80);
    } else {
        n = rnd.next(81, 100);
    }

    println(n);
    return 0;
}
