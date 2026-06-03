#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int a;
    int b;

    if (mode == 0) {
        a = rnd.next(-100, 100);
        b = 0;
    } else if (mode == 1) {
        a = rnd.any(std::vector<int>{-100, 100});
        b = rnd.next(-100, 100);
    } else if (mode == 2) {
        a = rnd.next(-100, 100);
        b = rnd.any(std::vector<int>{-100, 100});
    } else if (mode == 3) {
        a = rnd.next(-100, 100);
        b = a;
    } else if (mode == 4) {
        a = rnd.next(-100, 100);
        b = -a;
    } else {
        a = rnd.next(-100, 100);
        b = rnd.next(-100, 100);
    }

    println(a, b);
    return 0;
}
