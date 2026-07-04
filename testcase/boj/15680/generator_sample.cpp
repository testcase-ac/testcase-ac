#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    println(rnd.next(0, 1));
    return 0;
}
