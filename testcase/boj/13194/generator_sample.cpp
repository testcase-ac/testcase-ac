#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // The local validator mirrors the official full-size specification only.
    println(1250, 500000, 500000);

    return 0;
}
