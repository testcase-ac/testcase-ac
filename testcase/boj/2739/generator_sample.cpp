#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    println(rnd.next(1, 9));

    return 0;
}
