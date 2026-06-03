#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A = rnd.next(1, 4);
    int B = rnd.next(1, 4);

    println(A, B);
    return 0;
}
