#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 2);
    } else if (mode == 1) {
        n = rnd.next(3, 10);
    } else if (mode == 2) {
        n = rnd.next(11, 100);
    } else if (mode == 3) {
        n = rnd.next(101, 1000);
    } else if (mode == 4) {
        n = rnd.next(1001, 2016);
    } else {
        n = 2017;
    }

    println(n);
    return 0;
}
