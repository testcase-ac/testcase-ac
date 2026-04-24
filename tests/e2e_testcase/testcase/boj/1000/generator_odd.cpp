#include "testlib.h"
#include <iostream>

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    int a = rnd.next(1, 5000) * 2 - 1;
    int b = rnd.next(1, 5000) * 2 - 1;
    std::cout << a << ' ' << b << '\n';
    return 0;
}
